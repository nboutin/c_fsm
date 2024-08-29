/**
 * \file test_fsm_null.h
 * \brief Test FSM
 * \date 2024-08
 * \author Nicolas Boutin
 */

#include "gmock/gmock.h"

extern "C" {
#include "fsm/fsm.h"
#include "fsm_on_off.h"
}

using namespace testing;

class FSM_test_null : public ::testing::Test {
protected:
  void SetUp() {}
  fsm_t fsm;
};

TEST_F(FSM_test_null, fsm_init_null)
{
  fsm_init(&fsm, NULL);
  fsm_init(NULL, &off_state);
  fsm_init(NULL, NULL);
  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, fsm_trigger_null)
{
  fsm_trigger(NULL, &off_event);
  fsm_trigger(&fsm, NULL);
  fsm_trigger(NULL, NULL);
  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, fsm_trigger_null_current_state)
{
  fsm_init(&fsm, NULL);
  fsm_trigger(&fsm, &off_event);
  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, fsm_trigger_null_transition_no_next_state)
{
  fsm_init(&fsm, &off_state);

  struct fsm_transition_s* transition_list_backup = off_state.transition_list;

  static fsm_transition_s transition_list_test[] = {
      {event_type_on, NULL}
  };
  off_state.transition_list = transition_list_test;
  fsm_trigger(&fsm, &on_event);
  off_state.transition_list = transition_list_backup;
  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, next_state_is_not_current_state_without_exit_action)
{
  fsm_init(&fsm, &off_state);

  fsm_action_t off_exit_action_backup = off_state.exit_action;
  off_state.exit_action               = NULL;

  fsm_trigger(&fsm, &on_event);

  off_state.exit_action = off_exit_action_backup;
  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, next_state_is_current_state_without_exit_action)
{
  fsm_init(&fsm, &off_state);

  fsm_action_t off_exit_action_backup = off_state.exit_action;
  off_state.exit_action               = NULL;

  off_state.transition_list[0].next_state = &off_state;

  fsm_trigger(&fsm, &on_event);

  off_state.exit_action                   = off_exit_action_backup;
  off_state.transition_list[0].next_state = &on_state;

  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, next_state_is_not_current_state_with_entry_action)
{
  fsm_init(&fsm, &off_state);

  fsm_action_t on_entry_action_backup = on_state.entry_action;
  on_state.entry_action               = NULL;

  fsm_trigger(&fsm, &on_event);

  on_state.entry_action = on_entry_action_backup;
  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, next_state_is_current_state_with_entry_action)
{
  fsm_init(&fsm, &off_state);

  fsm_action_t on_entry_action_backup = on_state.entry_action;
  on_state.entry_action               = NULL;

  on_state.transition_list[0].next_state = &on_state;

  fsm_trigger(&fsm, &on_event);

  on_state.entry_action                  = on_entry_action_backup;
  on_state.transition_list[0].next_state = &off_state;

  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, final_state_reached)
{
  fsm_init(&fsm, &off_state);

  size_t count              = on_state.transition_count;
  on_state.transition_count = 0;
  fsm_trigger(&fsm, &on_event);

  on_state.transition_count = count;
  ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, get_transition_current_state_null_event_null)
{
    fsm_init(&fsm, &off_state);

    struct fsm_state_s* state_backup = fsm.current_state;
    fsm.current_state = NULL;

    fsm_trigger(&fsm, NULL);

    fsm.current_state = state_backup;
    ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, get_transition_current_state_null)
{
    fsm_init(&fsm, &off_state);

    struct fsm_state_s* state_backup = fsm.current_state;
    fsm.current_state = NULL;

    fsm_trigger(&fsm, &on_event);

    fsm.current_state = state_backup;
    ASSERT_TRUE(true);
}

TEST_F(FSM_test_null, get_transition_event_null)
{
    fsm_init(&fsm, &off_state);

    fsm_trigger(&fsm, NULL);
    ASSERT_TRUE(true);
}
