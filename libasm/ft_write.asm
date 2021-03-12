global ft_write

section .text

ft_write:
	mov rax, 1 ; meto en rax el codigo de la syscall write
	syscall
	ret