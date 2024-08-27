
#pragma once

#include <stdint.h>

#include "fsm/fsm.h"

extern uint32_t test_counter;

extern struct fsm_event_s on_event, off_event;
extern struct fsm_state_s on_state, off_state;
