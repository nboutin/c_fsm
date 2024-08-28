
#include <stdbool.h>

#include "fsm_on_off.h"

uint32_t test_counter = 0;

typedef enum {
  event_type_on,
  event_type_off,
} event_type_t;

struct fsm_event_s on_event  = {.event_type = event_type_on, .data = &test_counter};
struct fsm_event_s off_event = {.event_type = event_type_off, .data = &test_counter};

static void on_entry_action(struct fsm_event_s* event);
static void on_exit_action(struct fsm_event_s* event);
static void off_entry_action(struct fsm_event_s* event);
static void off_exit_action(struct fsm_event_s* event);

struct fsm_state_s off_state = {
    .transition_list =
        (struct fsm_transition_s[]){
                                    {event_type_on, &on_state},
                                    },
    .transition_count = 1,
    .entry_action     = off_entry_action,
    .exit_action      = off_exit_action,
};

struct fsm_state_s on_state = {
    .transition_list =
        (struct fsm_transition_s[]){
                                    {event_type_off, &off_state},
                                    },
    .transition_count = 1,
    .entry_action     = on_entry_action,
    .exit_action      = on_exit_action,
};

static void on_entry_action(struct fsm_event_s* event)
{
  uint32_t* counter = (uint32_t*) event->data;
  *counter += 1;
}

static void on_exit_action(struct fsm_event_s* event)
{
  uint32_t* counter = (uint32_t*) event->data;
  *counter += 10;
}

static void off_entry_action(struct fsm_event_s* event)
{
  uint32_t* counter = (uint32_t*) event->data;
  *counter += 100;
}

static void off_exit_action(struct fsm_event_s* event)
{
  uint32_t* counter = (uint32_t*) event->data;
  *counter += 1000;
}
