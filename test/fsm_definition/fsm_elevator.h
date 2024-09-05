#pragma once

#include <stdint.h>

#include "fsm/fsm.h"

extern bool guard_flag;

extern struct fsm_event_s open_event, close_event, lock_event, unlock_event;
extern struct fsm_state_s closed_state, opened_state, locked_state;
