#include <stdio.h>
#include "LedSM.h"

void ledInitData(LedData *data)  {
  data->state = LED_OFF;
}

void ledSM(LedData *data) {
    switch(data->state)  {
        case LED_OFF:
            turnOffLED1();

            if(msg == CHANGE_MODE) {
                data->state = LED_BLINKING_ON;
                msg = DO_NOTHING;
            }
            break;

        case LED_BLINKING_ON:
            turnOnLED1();

            if(msg == CHANGE_MODE) {
                data->state = LED_ON;
                msg = DO_NOTHING;
            }

            else {
                if(oneHundredMiliSecHasNotExpired())
                    data->state = LED_BLINKING_OFF;
            }
            break;

        case LED_BLINKING_OFF:
            turnOffLED1();

            if(msg == CHANGE_MODE) {
                data->state = LED_ON;
                msg = DO_NOTHING;
            }

            else {
                if(oneHundredMiliSecHasNotExpired())
                    data->state = LED_BLINKING_ON;
            }
            break;

        case LED_ON:
            turnOnLED1();

            if(msg == CHANGE_MODE) {
                data->state = LED_OFF;
                msg = DO_NOTHING;
            }
            break;

        default:
            printf("Error: unknown state encountered in ledSM: %d\n", data->state);
            break;
  }
}