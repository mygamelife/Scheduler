#ifndef LedSM_H
#define LedSM_H

#include <stdint.h>
#include "State.h"
#include "Timer.h"
#include "Message.h"
#include "Button.h"
#include "LED.h"

typedef struct {
  State state;
  uint32_t time;
} LedData;

#endif // LedSM_H
