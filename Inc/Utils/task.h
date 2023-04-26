#ifndef UTILS_TASK_H
#define UTILS_TASK_H

#include "Utils/event_queue.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_TIMEOUT_MS(X) (X * 1000)
#define TASK_TIMEOUT_S(X) (TASK_TIMEOUT_MS(X) * 1000)

typedef void (*TaskStateCallback)(Events);

typedef struct Task
{
    TaskStateCallback state_cb;
    bool task_have_timeout;
    uint32_t task_timeout_us;
    uint32_t task_timeout_counter;
    EventQueue queue;
} Task;

void task_init(Task *task, TaskStateCallback state, uint32_t timeout_us);
void task_register_event(Task *task, Events event);
void task_exec(Task *task);
void task_state_transit_with_timeout(Task *task, TaskStateCallback state, uint32_t timeout_us);
void task_state_transit(Task *task, TaskStateCallback state);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_TASK_H */