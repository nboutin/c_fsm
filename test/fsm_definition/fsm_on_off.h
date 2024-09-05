
#pragma once

#include <stdint.h>

#include "fsm/fsm.h"

extern uint32_t test_counter;

typedef enum {
  event_type_on,
  event_type_off,
} event_type_t;

extern struct fsm_event_s on_event, off_event;
extern struct fsm_state_s on_state, off_state;
