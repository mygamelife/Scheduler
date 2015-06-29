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
  CpuCortex *context;
  
  mainTcb.name = "main thread";
  mainTcb.sp = 0;
  taskOneTcb.name = "thread #1";
  taskOneTcb.sp = (uint32_t)&taskOneStack[1028];
  context = (CpuCortex*)(((uint32_t)&taskOneStack[1028]) - sizeof(CpuCortex));
  context->XPSR = 0x0FFFFFF0;
  context->PC   = 0xEEEEEEEE;
  context->LR   = 0xDDDDDDDD;
  context->R12  = 0xCCCCCCCC;
  context->R3   = 0x33333333;
  context->R2   = 0x22222222;
  context->R1   = 0x11111111;
  context->R0   = 0x00000000;
  context->R11  = 0xBBBBBBBB;
  context->R10  = 0xAAAAAAAA;
  context->R9   = 0x99999999;
  context->R8   = 0x88888888;
  context->R7   = 0x77777777;
  context->R6   = 0x66666666;
  context->R5   = 0x55555555;
  context->R4   = 0x44444444;
}
