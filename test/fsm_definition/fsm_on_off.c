
#include <stdbool.h>

#include "fsm_on_off.h"

uint32_t test_counter = 0;

struct fsm_event_s on_event  = {.event_type = event_type_on, .data = &test_counter};
struct fsm_event_s off_event = {.event_type = event_type_off, .data = &test_counter};

static void update_counter_by_order(uint32_t* counter, uint32_t order);

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
  update_counter_by_order(counter, 1);
}

static void on_exit_action(struct fsm_event_s* event)
{
  uint32_t* counter = (uint32_t*) event->data;
  update_counter_by_order(counter, 2);
}

static void off_entry_action(struct fsm_event_s* event)
{
  uint32_t* counter = (uint32_t*) event->data;
  update_counter_by_order(counter, 3);
}

static void off_exit_action(struct fsm_event_s* event)
{
  uint32_t* counter = (uint32_t*) event->data;
  update_counter_by_order(counter, 4);
}

static void update_counter_by_order(uint32_t* counter, uint32_t order)
{
  if ((*counter % 10) == 0)
  {
    *counter += order;
  }
  else if (((*counter / 10) % 10) == 0)
  {
    *counter += order * 10;
  }
  else if (((*counter / 100) % 10) == 0)
  {
    *counter += order * 100;
  }
  else if (((*counter / 1000) % 10) == 0)
  {
    *counter += order * 1000;
  }
}
