/**
 * \file fsm.c
 * \brief Finite State Machine library
 * \date 2024-08
 * \author Nicolas Boutin
 */

#include <stddef.h>

#include "fsm.h"

// --- Private functions

static struct fsm_transition_s* _fsm_get_transition(const struct fsm_state_s* state, const struct fsm_event_s* event);

// --- Public functions

/**
 * \details Does not call entry_action of entry_state because there is no event
 */
void fsm_init(fsm_t* fsm, struct fsm_state_s* entry_state)
{
  if (fsm == NULL)
  {
    return;
  }
  fsm->current_state = entry_state;
}

void fsm_trigger(fsm_t* fsm, struct fsm_event_s* event)
{
  if ((fsm == NULL) || (event == NULL))
  {
    return;
  }

  if (fsm->current_state == NULL)
  {
    return; // TODO goto error_callback
  }

  // Check no transition defined

  struct fsm_state_s* next_state = fsm->current_state;

  do
  {
    struct fsm_transition_s* transition = _fsm_get_transition(next_state, event);

    // If no transition for the given (state, event)
    // check for any transition for any of the parents state, if any.
    if (transition == NULL)
    {
      // TODO check parent state for transitions
      continue;
    }

    if (transition->next_state == NULL)
    {
      // TODO goto error
      return;
    }
    next_state = transition->next_state;

    // TODO if new state is parent_state, enter its entry state
    // TODO run exit action
    // TODO run transition action

    // Call the new state's entry action if it does not return to itself
    if ((next_state != fsm->current_state) && (next_state->entry_action))
    {
      // TODO pass state_data to entry_action : next_state->entry_action(nextState->data, event);
      next_state->entry_action(event);
    }

    // TODO Store previous state
    fsm->current_state = next_state;
    // TODO Check for state loop on itself
    // TODO Check new_state == error state

    // Check for final_state reached
    if (fsm->current_state->transition_count == 0)
    {
      return;
    }
    return;
  } while (next_state);
  return;
}

// --- Private functions

static struct fsm_transition_s* _fsm_get_transition(const struct fsm_state_s* state, const struct fsm_event_s* event)
{
  if ((state == NULL) || (event == NULL))
  {
    return NULL;
  }

  for (size_t transition_i = 0; transition_i < state->transition_count; transition_i++)
  {
    struct fsm_transition_s* transition = &state->transition_list[transition_i];

    if ((transition != NULL) && (transition->event_type == event->event_type))
    {
      // TODO Handle guard condition here
      return transition;
    }
  }
  // No transition found for given state
  return NULL;
}
