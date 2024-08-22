/**
 * \file fsm.h
 * \brief Finite State Machine library
 * \date 2024-08
 * \author Nicolas Boutin
 */

#pragma once

#include <stdint.h>

// --- Forward declaration

typedef struct fsm_transition_s fsm_transition_t;

// --- Public types

typedef int32_t fsm_event_type_t;

typedef struct {
  fsm_transition_t* transition_list;
  size_t transition_count;
  // entry action
  // on_state
  // exit action
} fsm_state_t;

typedef struct {
  fsm_event_type_t event_type;
} fsm_event_t;

struct fsm_transition_s {
  fsm_event_type_t event_type;
  fsm_state_t* next_state;
  // start state
  // event
  // target state
  // Action
  // Guard
};

typedef struct {
  fsm_state_t* current_state;
  // previous_state
  // event_mailbox
} fsm_t;

void fsm_init(fsm_t* fsm, fsm_state_t* entry_state);
void fsm_trigger(fsm_t* fsm, fsm_event_t* event);

// void fsm_init (entry_state, entry_action)
// bool fsm_process
// fsm_trigger
// fsm_get_current_state
