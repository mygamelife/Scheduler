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
    ldr     r0,   =#0xAAAAA
    ldr     r1,   =#0x11111
    ldr     r2,   =#0x22222
    ldr     r3,   =#0x33333
    ldr     r4,   =#0x44444
    ldr     r5,   =#0x55555
    ldr     r6,   =#0x66666
    ldr     r7,   =#0x77777
    ldr     r8,   =#0x88888
    ldr     r9,   =#0x99999
    ldr     r10,  =#0x0AAA0
    ldr     r11,  =#0x1BBB1
    ldr     r12,  =#0x2CCC2
    ldr     lr,   =#0x3DDD3
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
