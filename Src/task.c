#include "Utils/task.h"

void task_init(Task *task, TaskStateCallback state, uint32_t timeout_us)
{
    task->state_cb = state;
    task->task_have_timeout = timeout_us == 0 ? false : true;
    task->task_timeout_us = timeout_us;
    task->task_timeout_counter = 0;
    event_queue_init(&task->queue);
    task->state_cb(EVENT_ENTER_STATE);
}

void task_register_event(Task *task, Events event)
{
    event_queue_bus_register(&task->queue, event);
}

void task_exec(Task *task)
{
    task->state_cb(event_queue_pop_event(&task->queue));
}

void task_state_transit_with_timeout(Task *task, TaskStateCallback state, uint32_t timeout_us)
{
    task->task_have_timeout = timeout_us == 0 ? false : true;
    task->task_timeout_us = timeout_us;
    task_state_transit(task, state);
}

void task_state_transit(Task *task, TaskStateCallback state)
{
    task->state_cb(EVENT_EXIT_STATE);
    task->state_cb = state;
    task->task_timeout_counter = 0;
    task->state_cb(EVENT_ENTER_STATE);
}