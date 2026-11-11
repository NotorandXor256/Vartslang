.intel_syntax noprefix

.section .bss

.section .data
exit:
  mov rax, 60 
  mov rdi, 0
  syscall
