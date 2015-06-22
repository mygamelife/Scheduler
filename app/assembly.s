  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global  testFunc

  .section  .text.testFunc
  .type  testFunc, %function
testFunc:
  movs   r0, #0x12
  movs   r1, #0x30
  movs   r2, #0x57
  ldr	 r3, =0x1234ABCD
  movw.w r4, 0x1234
  movt.w r4, 0xABCD
  //push {r0, r1}
  //pop {r10, r11}

  //decrement after
  //push r1 -> r0 (pointing r0)
   * 0x2001FFE0		|_r1_|
   * 0x2001FFDC		|_r0_| <-- pointing
   * 				|____|
   * 				|____|
   * 				|____|
  stmdb sp!, {r0,r1}
  //increment after
  //pop r0 -> r1
  ldmia sp!, {r10,r11}
  /*
  --------TEST---------
  push		{lr} //save the link register first otherwise cant return to callee
  movs		r1, #12
  bl		dummy
  pop		{lr}
  */
  bx    lr
