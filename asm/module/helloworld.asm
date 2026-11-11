.intel_syntax noprefix
.section .data
msg:
  .ascii "Hello World\n"

.text
  .globl _start

_start:
  mov rax, 1 
  mov rdi, 1
  lea rsi, [msg]
  mov rdx, 13
  syscall
exit:
  mov rax, 60
  mov rdi, 1
  syscall
