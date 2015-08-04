    .syntax unified
    .cpu cortex-m4
    .fpu softvfp
    .thumb

    .global   taskSwitch
    .global   SysTick_Handler
    .extern   taskOneStack;
    .extern   taskTwoStack;
    .extern   head;
     
  	.section  .text.taskSwitch
  	.type taskSwitch, %function
    
    //MainTask
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
    b       .

    .align 8
    .type   SysTick_Handler, %function
    //#define in arm assembly
    .equ TCB.NEXT,  0
    .equ TCB.NAME,  4
    .equ TCB.SP,    8

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
    push    	{r4-r11}			//push all neccessary register to stack
    ldr     	r4,	=runningTcb		//mainTcb
    ldr     	r4,	[r4]			//r4 pointing to mainTcb
    str     	sp,	[r4, #TCB.SP]		//manTcb.sp = cuurent sp
    push	{lr}			//save current lr
    ldr		r0,	=readyQueue	//load readyQueeue address to r0 (readyQueue pointing to taskOneTcb)
    bl		listRemoveHead		//remove taskOneTcb from readyQueue
    mov		r5,	r0		//store taskOneTcb to r5
    ldr		r1, =runningTcb		//load runningTcb address to r1 (runningTcb pointing to mainTcb)
    str		r0, [r1]		//Instead of pointing to mainTcb now
					//runningTcb is pointing TaskOneTcb
    ldr		r0,	=readyQueue		//load readyQueeue address to r0 (readyQueeue poinitng to NULL)
    mov		r1,	r4		//r4 contain mainTcb that we have store previously
					//we cant use r1 direcly because the current address it pointing
					//to is taskOneTcb
    bl		addLinkedList		//store mainTcb into readyQueue
    pop		{lr}
    ldr		sp,	[r5, #TCB.SP]	//current sp pointing to taskOneTcb.sp
    pop     	{r4-r11}
    bx      	lr
