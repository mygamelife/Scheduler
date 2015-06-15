#ifndef ButtonSM_H
#define ButtonSM_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#include "State.h"

typedef struct {
  State state;
} ButtonData;

#endif // ButtonSM_H
