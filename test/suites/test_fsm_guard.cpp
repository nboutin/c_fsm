/**
 * \file test_fsm_guard.h
 * \brief Test FSM
 * \date 2024-09
 * \author Nicolas Boutin
 */

#include "gmock/gmock.h"

extern "C" {
#include "fsm/fsm.h"
#include "fsm_elevator.h"
}

using namespace testing;

class FSM_test_guard : public ::testing::Test {
protected:
  void SetUp()
  {
    guard_flag = false;
    fsm_init(&fsm, &closed_state);
  }
  fsm_t fsm;
};

TEST_F(FSM_test_guard, guard_condition_true)
{
    guard_flag = true;
    fsm_trigger(&fsm, &open_event);

    EXPECT_EQ(&opened_state, fsm_get_current_state(&fsm));
}

TEST_F(FSM_test_guard, guard_condition_false)
{
    guard_flag = false;
    fsm_trigger(&fsm, &open_event);

    EXPECT_EQ(&closed_state, fsm_get_current_state(&fsm));
}
