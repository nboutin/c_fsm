
#include "fsm_elevator.h"

typedef enum {
  open_evt,
  close_evt,
  lock_evt,
  unlock_evt,
} event_type_t;

struct fsm_event_s open_event = {
    .event_type = open_evt,
    .data       = NULL,
};

struct fsm_event_s close_event = {
    .event_type = close_evt,
    .data       = NULL,
};

struct fsm_event_s lock_event = {
    .event_type = lock_evt,
    .data       = NULL,
};

struct fsm_event_s unlock_event = {
    .event_type = unlock_evt,
    .data       = NULL,
};

bool guard_flag = false;

bool guard(const fsm_condition_t condition, const struct fsm_event_s* event)
{
  return guard_flag;
}

// State Closed

#define closed_transitions_count 1U
struct fsm_transition_s closed_transitions[closed_transitions_count] = {
    {.event_type = open_evt, .next_state = &opened_state, .condition = NULL, .guard = guard},
};

struct fsm_state_s closed_state = {
    .transition_list  = closed_transitions,
    .transition_count = closed_transitions_count,
};

// State Opened

#define opened_transitions_count 1U
struct fsm_transition_s opened_transitions[opened_transitions_count] = {
    {close_evt, &closed_state},
};

struct fsm_state_s opened_state = {
    .transition_list  = opened_transitions,
    .transition_count = opened_transitions_count,
};

// State Locked

#define locked_transitions_count 1U
struct fsm_transition_s locked_transitions[locked_transitions_count] = {
    {unlock_evt, &closed_state},
};

struct fsm_state_s locked_state = {
    .transition_list  = locked_transitions,
    .transition_count = locked_transitions_count,
};
