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
    push	  {r0}
    b		    .

    .align 8
    .type   SysTick_Handler, %function
    
//   Decrement after
//   +-------+
//   |///////| <-	extra spaces depends on stack allign
//   +-------+
//   |  XPSR | 0x20000410
//   +-------+
//   |  PC   | 0x2000040C
//   +-------+
//   |  LR   | 0x20000408
//   +-------+
//   |  r12  | 0x20000404
//   +-------+
//   |  r3   | 0x20000400
//   +-------+
//   |  r2   | 0x200003FC
//   +-------+
//   |  r1   | 0x200003F8
//   +-------+
//   |  r0   | 0x200003F4
//   +-------+
//   |  r11  | 0x200003F0
//   +-------+
//   |  r10  | 0x200003EC
//   +-------+
//   |  r9   | 0x200003E8
//   +-------+
//   |  r8   | 0x200003E4
//   +-------+
//   |  r7   | 0x200003E4
//   +-------+
//   |  r6   | 0x200003E4
//   +-------+
//   |  r5   | 0x200003E4
//   +-------+
//   |  r4   | <-	sp
//   +-------+

SysTick_Handler:
    stmdb 	sp!,	{r4-r11}
    b       .

    
//Exercise
//#define in arm assembly
//.equ TCB.SP, 8
//.equ TCB.NEXT, 0
//.equ TCB.NAME, 4
//
//
//
//
//
//
//