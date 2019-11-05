#include <stdio.h>

int		main(void)
{
	char test[] = "prueba";
	ft_bzero(test, 3);
	printf("%s", test);
	return (0);
}
