global ft_strcmp

section .text

ft_strcmp:
	xor rax, rax ; rax = 0
	xor rcx, rcx ; rax = 0
	_loop:
		cmp BYTE [rdi + rcx], 0
		je _return
		cmp BYTE [rsi + rcx], 0
		je _return
		mov al, BYTE [rdi + rcx]
		cmp al, BYTE [rsi + rcx]
		jne _return
		inc rcx
		jmp _loop

_return:
	mov al, BYTE [rdi + rcx]
	sub al, BYTE [rsi + rcx]
	ret