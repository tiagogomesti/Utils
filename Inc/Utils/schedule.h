#ifndef UTILS_SCHEDULE_H
#define UTILS_SCHEDULE_H

#include "Utils/task.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TASKS 10

typedef uint64_t (*SystickFunctionCb)(void);

typedef struct Schedule
{
    Task *tasks[MAX_TASKS];
    uint8_t num_tasks;
    SystickFunctionCb systick_cb;
} Schedule;

void schedule_init(Schedule *schedule, SystickFunctionCb systick_cb);
void schedule_register_task(Schedule *g_schedule, Task *task);
void schedule_execute_sched(Schedule *schedule);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_SCHEDULE_H */