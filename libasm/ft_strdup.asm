global ft_strdup

extern malloc
extern ft_strcpy
extern ft_strlen

section .text
ft_strdup:
	xor rdx, rdx
	call ft_strlen ;llamo a strlen y mete en rax la longitud
	inc rax ; ++ a la longitud para el caracter nulo
	mov rdx, rdi ; guardo el string en otro registro
	mov rdi, rax ; meto la longitud del string en el primer parametro
	call malloc ; llamo a malloc, que guarda el nuevo puntero en rax
	mov rsi, rdx ; vuelvo a meter el string en rsi, parametro (source)
	mov rdi, rax ; el puntero que devuelve malloc lo meto al primer parametro (dest)
	call ft_strcpy ; llamo a strcpy con el puntero allocado en rdi y el string en rsi
	ret