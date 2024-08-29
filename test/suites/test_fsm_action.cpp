/**
 * \file test_fsm_action.h
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

class FSM_test_action : public ::testing::Test {
protected:
  void SetUp()
  {
    test_counter = 0;
    fsm_init(&fsm, &off_state);
  }
  fsm_t fsm;
};

TEST_F(FSM_test_action, dont_run_entry_action_from_fsm_init)
{
  EXPECT_EQ(test_counter, 0);
}

TEST_F(FSM_test_action, entry_action)
{
  fsm_trigger(&fsm, &on_event);
  EXPECT_EQ(test_counter, 14);
}

TEST_F(FSM_test_action, exit_action)
{
  fsm_trigger(&fsm, &on_event);
  fsm_trigger(&fsm, &off_event);
  EXPECT_EQ(test_counter, 3214);
}

TEST_F(FSM_test_action, current_state_exit_action_before_next_state_entry_action)
{
  fsm_trigger(&fsm, &on_event);
  fsm_trigger(&fsm, &off_event);
  EXPECT_EQ(test_counter, 3214);
}

TEST_F(FSM_test_action, same_state_from_init_state)
{
  fsm_trigger(&fsm, &off_event);
  EXPECT_EQ(test_counter, 0);
}

TEST_F(FSM_test_action, same_state_from_on_state)
{
  fsm_trigger(&fsm, &on_event);
  test_counter = 0;
  fsm_trigger(&fsm, &on_event);
  EXPECT_EQ(test_counter, 0);
}
