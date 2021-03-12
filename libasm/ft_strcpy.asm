global ft_strcpy

section .text
ft_strcpy:
	xor rcx, rcx
	xor rax, rax
	_loop:
		cmp BYTE [rsi + rcx], 0
		je _return
		mov al, BYTE [rsi + rcx]
		mov BYTE [rdi + rcx], al
		inc rcx
		jmp _loop

_return:
	mov BYTE [rdi + rcx], 0
	mov rax, rdi
	ret