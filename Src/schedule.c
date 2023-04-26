#include "Utils/schedule.h"
#include "Utils/event_queue.h"

void schedule_init(Schedule *schedule, SystickFunctionCb systick_cb)
{
    schedule->num_tasks = 0;
    schedule->systick_cb = systick_cb;
}

void schedule_register_task(Schedule *schedule, Task *task)
{
    if (schedule->num_tasks > MAX_TASKS)
    {
        return;
    }

    schedule->tasks[schedule->num_tasks] = task;
    (schedule->num_tasks)++;
}

static uint64_t schedule_time_passed(Schedule *schedule)
{
    static uint64_t tick_previous = 0;
    uint64_t time_passed = schedule->systick_cb() - tick_previous;

    if (time_passed > 0)
    {
        tick_previous += time_passed;
    }

    return time_passed;
}

static bool schedule_task_is_timeout(Task *task, uint64_t time_passed)
{
    if (!task->task_have_timeout)
    {
        return false;
    }
    task->task_timeout_counter += time_passed;

    if (task->task_timeout_counter > task->task_timeout_us)
    {
        task->task_timeout_counter = 0;
        return true;
    }

    return false;
}

void schedule_execute_sched(Schedule *schedule)
{
    uint64_t time_passed = 0;

    while (true)
    {
        time_passed = schedule_time_passed(schedule);

        for (uint8_t i = 0; i < schedule->num_tasks; i++)
        {
            Task *task = schedule->tasks[i];
            Events event = !schedule_task_is_timeout(task, time_passed) ? event_queue_pop_event(&task->queue)
                                                                        : EVENT_TIMEOUT_STATE;
            task->state_cb(event);
        }
    }
}
