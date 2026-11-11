.intel_syntax noprefix

.section .bss

.section .data

.section .text
print:
  mov rax, 1; write syscall
  mov rdi, 1; stdout
  lea rsi, []

exit:
  mov rax, 60
  mov rdi, 0
  syscall
