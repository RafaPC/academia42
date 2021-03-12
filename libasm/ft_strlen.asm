global ft_strlen

section .text

ft_strlen:
	mov rax, 0
	cmp BYTE [rdi + rax], 0
	jne ft_strlen_next
	ret

ft_strlen_next:
	inc rax
	cmp BYTE [rdi + rax], 0
	jne ft_strlen_next
	ret