/**
 * \file fsm.h
 * \brief Finite State Machine library
 * \date 2024-08
 * \author Nicolas Boutin
 */

#pragma once

#include <stdint.h>

// --- Forward declaration

// typedef struct fsm_transition_s fsm_transition_t;
struct fsm_state_s;
struct fsm_event_s;
struct fsm_transition_s;

// --- Public types

typedef int32_t fsm_event_type_t;
typedef void* fsm_event_data_t;

struct fsm_event_s {
  fsm_event_type_t event_type;
  fsm_event_data_t data;
};

// void ( *entryAction )( void *state_data, struct event *event );
// typedef void* fsm_data_t;
typedef void (*fsm_action_t)(struct fsm_event_s* event);

struct fsm_state_s {
  struct fsm_transition_s* transition_list;
  size_t transition_count;
  fsm_action_t entry_action;
  fsm_action_t exit_action;
};

struct fsm_transition_s {
  fsm_event_type_t event_type;
  struct fsm_state_s* next_state;
};

typedef struct {
  struct fsm_state_s* current_state;
  // previous_state
  // event_mailbox
} fsm_t;

void fsm_init(fsm_t* fsm, struct fsm_state_s* entry_state);
void fsm_trigger(fsm_t* fsm, struct fsm_event_s* event);

// void fsm_init (entry_state, entry_action)
// bool fsm_process
// fsm_trigger
// fsm_get_current_state
