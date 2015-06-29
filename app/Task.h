#ifndef Task_H
#define Task_H

#include <stdint.h>

typedef struct  {
  char      *name;
  uint32_t  sp;
} Tcb;

extern uint8_t taskOneStack[1028];
extern uint8_t taskTwoStack[1028];

void taskOne(void);

#endif // Task_H
