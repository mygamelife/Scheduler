#include "unity.h"
#include "ButtonSM.h"
#include "Message.h"
#include "mock_Button.h"

void setUp(void){}

void tearDown(void){}

void test_ButtonSM_if_state_is_RELEASE_and_buttonStat_is_1_should_change_state_to_PRESS()
{
  ButtonData buttonData;
  
  buttonInitData(&buttonData);
  
  buttonStat_ExpectAndReturn(1);
  buttonSM(&buttonData);
  TEST_ASSERT_EQUAL(buttonData.state, PRESS);
}

void test_ButtonSM_if_state_is_PRESS_buttonStat_is_1_should_stay_state_if_0_change_state()
{
  ButtonData buttonData;
  buttonData.state = PRESS;
  
  buttonStat_ExpectAndReturn(1);
  buttonSM(&buttonData);
  TEST_ASSERT_EQUAL(buttonData.state, PRESS);
  
  buttonStat_ExpectAndReturn(0);
  buttonSM(&buttonData);
  TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
}