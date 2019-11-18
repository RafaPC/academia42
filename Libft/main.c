#include <stdio.h>
#include "libft.h"

int main(int argc, char const *argv[])
{
	char *x = (char*)argv[1];
	if(ft_isalpha(x[0]))
		printf("true");
	else
		printf("false");
	return 0;
}
