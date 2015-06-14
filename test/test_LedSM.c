#include "unity.h"
#include "Message.h"
#include "State.h"
#include "ButtonSM.h"
#include "LedSM.h"
#include "mock_Button.h"
#include "mock_Timer.h"
#include "mock_LED.h"

void setUp(void){}

void tearDown(void){}

void test_LedSM_button_is_press_LedSM_should_change_state_to_LED_Blinking_ON()
{
    msg = DO_NOTHING;

    ButtonData buttonData;
    LedData ledData;

    buttonInitData(&buttonData);
    ledInitData(&ledData);

    buttonStat_ExpectAndReturn(1);
    turnOffLED1_Expect();

    buttonSM(&buttonData);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
}

void test_LedSM_LED_Blinking_ON_shouldnt_change_state_to_LED_BLINKING_OFF_when_timer_is_not_expired()
{
    msg = DO_NOTHING;

    LedData ledData;
    ledData.state = LED_BLINKING_ON;

    turnOnLED1_Expect();
    oneHundredMiliSecHasNotExpired_ExpectAndReturn(0);

    ledSM(&ledData);

    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
}

void test_LedSM_LED_Blinking_ON_should_change_state_to_LED_BLINKING_OFF_when_timer_is_expired()
{
    msg = DO_NOTHING;

    LedData ledData;
    ledData.state = LED_BLINKING_ON;

    turnOnLED1_Expect();
    oneHundredMiliSecHasNotExpired_ExpectAndReturn(1);

    ledSM(&ledData);

    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_OFF);
}

void test_LedSM_LED_Blinking_OFF_should_change_state_to_LED_BLINKING_ON_when_timer_is_expired()
{
    msg = DO_NOTHING;

    LedData ledData;
    ledData.state = LED_BLINKING_OFF;

    turnOffLED1_Expect();
    oneHundredMiliSecHasNotExpired_ExpectAndReturn(1);

    ledSM(&ledData);

    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
}

void test_LedSM_LED_Blinking_ON_should_change_state_to_LED_ON_when_Button_is_press()
{
    msg = DO_NOTHING;

    ButtonData buttonData;
    buttonInitData(&buttonData);

    LedData ledData;
    ledData.state = LED_BLINKING_ON;

    buttonStat_ExpectAndReturn(1);
    turnOnLED1_Expect();

    buttonSM(&buttonData);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
}

void test_LedSM_LED_keep_blinking_when_Button_is_not_press()
{
    msg = DO_NOTHING;

    ButtonData buttonData;
    buttonInitData(&buttonData);

    LedData ledData;
    ledData.state = LED_BLINKING_ON;

    buttonStat_ExpectAndReturn(0);

    turnOnLED1_Expect();
    oneHundredMiliSecHasNotExpired_ExpectAndReturn(1);
    turnOffLED1_Expect();
    oneHundredMiliSecHasNotExpired_ExpectAndReturn(1);
    turnOnLED1_Expect();
    oneHundredMiliSecHasNotExpired_ExpectAndReturn(1);

    buttonSM(&buttonData);
    ledSM(&ledData);
    ledSM(&ledData);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_OFF);
}

void test_LedSM_LED_Blinking_OFF_should_change_state_to_LED_ON_when_Button_is_press()
{
    msg = DO_NOTHING;

    ButtonData buttonData;
    buttonInitData(&buttonData);

    LedData ledData;
    ledData.state = LED_BLINKING_OFF;

    buttonStat_ExpectAndReturn(1);
    turnOffLED1_Expect();

    buttonSM(&buttonData);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
}

void test_LedSM_LED_ON_shouldnt_change_state_when_Button_is_not_press()
{
    msg = DO_NOTHING;

    ButtonData buttonData;
    buttonInitData(&buttonData);

    LedData ledData;
    ledData.state = LED_ON;

    buttonStat_ExpectAndReturn(0);
    turnOnLED1_Expect();

    buttonSM(&buttonData);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
}

void test_LedSM_LED_ON_should_change_state_to_LED_OFF_when_Button_is_press()
{
    msg = DO_NOTHING;

    ButtonData buttonData;
    buttonInitData(&buttonData);

    LedData ledData;
    ledData.state = LED_ON;

    buttonStat_ExpectAndReturn(1);
    turnOnLED1_Expect();

    buttonSM(&buttonData);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);

    buttonStat_ExpectAndReturn(0);
    turnOffLED1_Expect();

    buttonSM(&buttonData);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);
}