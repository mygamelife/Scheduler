#include <stdio.h>
#include "ButtonSM.h"
#include "Message.h"
#include "Button.h"

void buttonInitData(ButtonData *data)  {
  data->state = RELEASE;
}

void buttonSM(ButtonData *data) {
  switch(data->state)  {
    case RELEASE:
      if(buttonStat()) {
        data->state = PRESS;
        msg = CHANGE_MODE;
      }
    break;

    case PRESS:
      if(!buttonStat())  {
        data->state = RELEASE;
        msg = DO_NOTHING;
      }
      break;

    default:
      printf("Error: unknown state encountered in buttonSM: %d\n", data->state);
      break;
  }
}
