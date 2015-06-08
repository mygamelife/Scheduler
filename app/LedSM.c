#include <stdio.h>
#include "LedSM.h"
#include "Message.h"

void ledInitData(LedData *data)  {
  data->state = LED_OFF;
}

void ledSM(LedData *data) {
  switch(data->state)  {
    case LED_OFF:
      if(msg == CHANGE_MODE)  {
        data->state = LED_ON;
        msg = DO_NOTHING;
      }
      break;

    case LED_ON:
      break;
      
    default:
      printf("Error: unknown state encountered in ledSM: %d\n", data->state);
      break;
  }
}