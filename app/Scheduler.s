    .syntax unified
    .cpu cortex-m4
    .fpu softvfp
    .thumb

    .global   taskSwitch
    .global   SysTick_Handler
    .extern   taskOneStack;
    .extern   taskTwoStack;
     
  	.section  .text.taskSwitch
  	.type taskSwitch, %function
    
taskSwitch:
    ldr     r0,   =#0xAAAAAAAA
    ldr     r1,   =#0x11111111
    ldr     r2,   =#0x22222222
    ldr     r3,   =#0x33333333
    ldr     r4,   =#0x44444444
    ldr     r5,   =#0x55555555
    ldr     r6,   =#0x66666666
    ldr     r7,   =#0x77777777
    ldr     r8,   =#0x88888888
    ldr     r9,   =#0x99999999
    ldr     r10,  =#0x0AAAAAA0
    ldr     r11,  =#0xBBBBBBBB
    ldr     r12,  =#0xCCCCCCCC
    ldr     lr,   =#0xDDDDDDDD
    push	{r0}
    b		    .

    .align 8
    .type   SysTick_Handler, %function
    //#define in arm assembly
    .equ TCB.NAME,  0
    .equ TCB.SP,    4
//   Decrement after
//   +-------+
//   |///////| <-	extra spaces depends on stack allign
//   +-------+
//   |  XPSR |
//   +-------+
//   |  PC   |
//   +-------+
//   |  LR   |
//   +-------+
//   |  r12  |
//   +-------+
//   |  r3   |
//   +-------+
//   |  r2   |
//   +-------+
//   |  r1   |
//   +-------+
//   |  r0   |
//   +-------+
//   |  r11  |
//   +-------+
//   |  r10  |
//   +-------+
//   |  r9   |
//   +-------+
//   |  r8   |
//   +-------+
//   |  r7   |
//   +-------+
//   |  r6   |
//   +-------+
//   |  r5   |
//   +-------+
//   |  r4   | <-	sp
//   +-------+

SysTick_Handler:
    stmdb 	sp!, {r4-r11}
    push    {lr}
    ldr     r0,  =mainTcb
    ldr     sp,  [r0, #TCB.SP]
    ldr     r0,  =taskOneTcb
    ldr     sp,  [r0, #TCB.SP]
    pop     {lr}
    bx      lr

