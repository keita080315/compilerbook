.globl main
main:
  stp x29, x30, [sp, #-16]!
  mov x29, sp
  mov x0, 4
  stp x0, xzr, [sp, #-16]!
  mov x0, 2
  stp x0, xzr, [sp, #-16]!
  mov x0, 15
  stp x0, xzr, [sp, #-16]!
  ldp x1, xzr, [sp], #16
  ldp x0, xzr, [sp], #16
  add x0, x0, x1
  stp x0, xzr, [sp, #-16]!
  ldp x1, xzr, [sp], #16
  ldp x0, xzr, [sp], #16
  mul x0, x0, x1
  stp x0, xzr, [sp, #-16]!
  mov x0, 9
  stp x0, xzr, [sp, #-16]!
  mov x0, 3
  stp x0, xzr, [sp, #-16]!
  ldp x1, xzr, [sp], #16
  ldp x0, xzr, [sp], #16
  mul x0, x0, x1
  stp x0, xzr, [sp, #-16]!
  ldp x1, xzr, [sp], #16
  ldp x0, xzr, [sp], #16
  sub x0, x0, x1
  stp x0, xzr, [sp, #-16]!
  mov x0, 3
  stp x0, xzr, [sp, #-16]!
  ldp x1, xzr, [sp], #16
  ldp x0, xzr, [sp], #16
  add x0, x0, x1
  stp x0, xzr, [sp, #-16]!
  mov x0, 11
  stp x0, xzr, [sp, #-16]!
  ldp x1, xzr, [sp], #16
  ldp x0, xzr, [sp], #16
  sdiv x0, x0, x1
  stp x0, xzr, [sp, #-16]!
  mov sp, x29
  ldp x29, x30, [sp], #16
  ret
