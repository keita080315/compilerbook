.globl main
main:
  stp x29, x30, [sp, #-16]!
  mov x29, sp
  mov x0, 4
  str x0, [sp, #-16]!
  mov x0, -2
  str x0, [sp, #-16]!
  mov x0, 15
  str x0, [sp, #-16]!
  ldr x1, [sp], #16
  ldr x0, [sp], #16
  add x0, x0, x1
  str x0, [sp, #-16]!
  ldr x1, [sp], #16
  ldr x0, [sp], #16
  mul x0, x0, x1
  str x0, [sp, #-16]!
  mov x0, 9
  str x0, [sp, #-16]!
  mov x0, 3
  str x0, [sp, #-16]!
  ldr x1, [sp], #16
  ldr x0, [sp], #16
  mul x0, x0, x1
  str x0, [sp, #-16]!
  ldr x1, [sp], #16
  ldr x0, [sp], #16
  sub x0, x0, x1
  str x0, [sp, #-16]!
  mov x0, 3
  str x0, [sp, #-16]!
  ldr x1, [sp], #16
  ldr x0, [sp], #16
  add x0, x0, x1
  str x0, [sp, #-16]!
  mov sp, x29
  ldp x29, x30, [sp], #16
  ret
