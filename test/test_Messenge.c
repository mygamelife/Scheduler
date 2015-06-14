#include <stdbool.h>
#include "unity.h"
#include "Message.h"
#include "ButtonSM.h"
#include "LedSM.h"
#include "mock_Button.h"
#include "mock_Timer.h"
#include "mock_LED.h"

void setUp(void){}

void tearDown(void){}

void test_message_passing_send_a_message_then_LedState_should_change_to_LED_ON()
{
  msg = DO_NOTHING;

  LedData ledData;
  ButtonData buttonData;

  buttonInitData(&buttonData);
  ledInitData(&ledData);

  turnOffLED1_Expect();

  ledSM(&ledData);
  TEST_ASSERT_EQUAL(ledData.state, LED_OFF);

  buttonStat_ExpectAndReturn(true);
  turnOffLED1_Expect();

  buttonSM(&buttonData);
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
}
