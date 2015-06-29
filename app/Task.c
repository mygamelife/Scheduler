#include "Task.h"

uint8_t taskOneStack[1028];
uint8_t taskTwoStack[1028];

Tcb mainTcb;
Tcb taskOneTcb;
Tcb taskTwoTcb;

void taskOne(void)  {
  return;
}

void initTcb()  {
  mainTcb.name = "main thread";
  mainTcb.sp = 0;
  
  taskOneTcb.name = "thread #1";
  taskOneTcb.sp = (uint8_t)&taskOneStack[1028];
}
