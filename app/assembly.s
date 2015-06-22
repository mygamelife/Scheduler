  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global  testFunc

  .section  .text.testFunc
  .type  testFunc, %function
testFunc:
  movs   r0, #0x12
  movs   r1, #0x34
  movs   r2, #0x57
  ldr	 r3, =0x1234ABCD
  movw.w		r4, 0x1234
  movt.w		r5, 0xABCD
  bx    lr
