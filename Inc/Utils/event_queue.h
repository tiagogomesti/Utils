#ifndef LIB_EVENT_QUEUE_H
#define LIB_EVENT_QUEUE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_EVENTS_QUEUE 10
#define MAX_EVENTS_LINESTER 10

typedef enum Events
{
    EVENT_NONE,
    EVENT_ENTER_STATE,
    EVENT_EXIT_STATE,
    EVENT_TIMEOUT_STATE,

    EVENT_100_US,
    EVENT_1_MS,
    EVENT_10_MS,
    EVENT_100_MS,
    EVENT_300_MS,
    EVENT_500_MS,
    EVENT_1_S,
} Events;

typedef void (*EventCb)(Events);

typedef struct EventQueue
{
    Events events[MAX_EVENTS_QUEUE];
    uint8_t head;
    uint8_t tail;
    bool is_queue_full;
} EventQueue;

void event_queue_bus_register(EventQueue *event_queue, Events event);
void event_queue_bus_send_event(Events event);

void event_queue_init(EventQueue *queue);
Events event_queue_pop_event(EventQueue *queue);
void event_queue_push_event(EventQueue *queue, Events event);

#ifdef __cplusplus
}
#endif

#endif /* LIB_EVENT_QUEUE_H */