#include "Utils/event_queue.h"

typedef struct EventQueueBus
{
    EventQueue *event_queue[MAX_EVENTS_LINESTER];
    uint8_t num_listers;
} EventQueueBus;

static EventQueueBus g_event_queue_bus[EVENT_MAX] = {0};

void event_queue_bus_register(EventQueue *event_queue, Events event)
{
    EventQueueBus *event_queue_bus = &g_event_queue_bus[event];

    if (event_queue_bus->num_listers >= MAX_EVENTS_LINESTER)
    {
        return;
    }

    uint8_t listener = event_queue_bus->num_listers;
    event_queue_bus->event_queue[listener] = event_queue;
    (event_queue_bus->num_listers)++;
}

void event_queue_bus_send_event(Events event)
{
    EventQueueBus *queue_bus = &g_event_queue_bus[event];

    for (uint8_t i = 0; i < queue_bus->num_listers; i++)
    {
        event_queue_push_event(queue_bus->event_queue[i], event);
    }
}

void event_queue_init(EventQueue *queue)
{
    queue->head = 0;
    queue->tail = 0;
    queue->is_queue_full = false;
}

static bool event_queue_is_empty(EventQueue *queue)
{
    return !queue->is_queue_full && (queue->head == queue->tail);
}

Events event_queue_pop_event(EventQueue *queue)
{
    if (event_queue_is_empty(queue))
    {
        return EVENT_NONE;
    }

    Events event = queue->events[queue->tail];
    queue->tail = ((queue->tail) + 1) % MAX_EVENTS_QUEUE;

    return event;
}

void event_queue_push_event(EventQueue *queue, Events event)
{
    if (queue->is_queue_full)
    {
        return;
    }

    queue->events[queue->head] = event;
    queue->head = ((queue->head) + 1) % MAX_EVENTS_QUEUE;

    if (queue->head == queue->tail)
    {
        queue->is_queue_full = true;
    }
}
