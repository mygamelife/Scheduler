#include "Task.h"

uint8_t taskOneStack[1028];
uint8_t taskTwoStack[1028];

Tcb mainTcb;
Tcb taskOneTcb;
Tcb taskTwoTcb;
Tcb *runningTcb;
Tcb *readyQueue;

void taskOne(void)  {
  //run one time only, use to identified task switch is correct
  asm(
    "ldr  r0, =#0xa000000a\n\t"
    "ldr  r1, =#0xb111111b\n\t"
    "ldr  r2, =#0xc222222c\n\t"
    "ldr  r3, =#0xd333333d\n\t"
  );
  while(1)
  {}
}

void initTcb()  {
  CpuCortex *context;
  
  /* MainTask */
  mainTcb.name = "main thread";
  mainTcb.sp = 0;
  
  /* TaskOne */
  taskOneTcb.name = "thread #1";
  taskOneTcb.sp = (uint32_t)&taskOneStack[1028];
  context = (CpuCortex*)(((uint32_t)&taskOneStack[1028]) - sizeof(CpuCortex));
  taskOneTcb.sp = (uint32_t)context;
  context->XPSR = 0x01000000;
  context->PC   = (uint32_t)taskOne;
  context->LR   = 0x0DDDDDD0;
  context->R12  = 0x0CCCCCC0;
  context->R3   = 0x03333330;
  context->R2   = 0x02222220;
  context->R1   = 0x01111110;
  context->R0   = 0x00000000;
  context->R11  = 0x0BBBBBB0;
  context->R10  = 0x0AAAAAA0;
  context->R9   = 0x09999990;
  context->R8   = 0x08888880;
  context->R7   = 0x07777770;
  context->R6   = 0x06666660;
  context->R5   = 0x05555550;
  context->R4   = 0x04444440;
  
  runningTcb = &mainTcb;
  readyQueue = &taskOneTcb;
}
