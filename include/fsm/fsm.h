/**
 * \file fsm.h
 * \brief Finite State Machine library
 * \date 2024-08
 * \author Nicolas Boutin
 */

#pragma once

// --- Public types

typedef struct
{
    // entry action
    // on_state
    // exit action
} fsm_state_t;

typedef struct
{
    // start state
    // event
    // target state
    // Action
    // Guard
} fsm_transition_t;

typedef struct
{
    // current_state
    // previous_state
    // event_mailbox
} fsm_t;

// fsm_init (entry_state, entry_action)
// bool fsm_process
// fsm_trigger
// fsm_get_current_state

