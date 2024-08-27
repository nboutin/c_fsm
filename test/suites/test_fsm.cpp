/**
 * \file test_fsm.h
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

class FSM_test : public ::testing::Test {
protected:
  void SetUp()
  {
    test_counter = 0;
    fsm_init(&fsm, &off_state);
  }
  fsm_t fsm;
};

TEST_F(FSM_test, dont_run_entry_action_from_fsm_init)
{
  EXPECT_EQ(test_counter, 0);
}

TEST_F(FSM_test, entry_action)
{
  fsm_trigger(&fsm, &on_event);
  EXPECT_EQ(test_counter, 1);
}
