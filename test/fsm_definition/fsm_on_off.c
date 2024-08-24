
#include "fsm_on_off.h"

typedef enum {
  event_type_on,
  event_type_off,
} event_type_t;

struct fsm_event_s on_event  = {.event_type = event_type_on};
struct fsm_event_s off_event = {.event_type = event_type_off};

struct fsm_state_s off_state = {
    .transition_list =
        (struct fsm_transition_s[]){
                                    {event_type_on, &on_state},
                                    },
    .transition_count = 1,
};

struct fsm_state_s on_state = {
    .transition_list =
        (struct fsm_transition_s[]){
                                    {event_type_off, &off_state},
                                    },
    .transition_count = 1,
};
