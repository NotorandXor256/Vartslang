.intel_syntax noprefix

.section .bss

.section .data

.section .text
  .global _start

_start:
  mov rax, 60 
  mov rdi, 0
  syscall
