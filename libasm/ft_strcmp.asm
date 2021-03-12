global ft_strcmp

section .text

ft_strcmp:
	xor rax, rax
	mov rcx, 0 ; tambien valdria xor rcx, rcx
	jmp first_check
	
first_check:
	cmp BYTE [rdi + rcx], 0
	jne second_check
	jmp _return

second_check:
	cmp BYTE [rsi + rcx], 0
	jne char_cmp
	jmp _return

char_cmp:
	mov ah, BYTE [rdi + rcx]
	cmp ah, BYTE [rsi + rcx]
	jne _return
	inc rcx
	jmp first_check

_return:
	mov ah, BYTE [rdi + rcx]
	sub ah, BYTE [rsi + rcx]
	ret