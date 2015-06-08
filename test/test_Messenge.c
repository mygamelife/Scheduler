#include <stdbool.h>
#include "unity.h"
#include "Message.h"
#include "ButtonSM.h"
#include "LedSM.h"
#include "mock_Button.h"

void setUp(void){}

void tearDown(void){}

void test_message_passing_send_a_message_then_LedState_should_change_to_LED_ON()
{
  LedData ledData;
  ButtonData buttonData;
  
	buttonInitData(&buttonData);
  ledInitData(&ledData);
  
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(ledData.state, LED_OFF);
  
  buttonStat_ExpectAndReturn(true);
  
  buttonSM(&buttonData);
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(ledData.state, LED_ON);
}
