int		ft_write(int fd, char *buff, int size);
int		ft_strlen(char *buff);
char	*ft_read(int fd, void *buf, int size);
int		ft_strcmp(char *s1, char *s2);
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/* code */
	char *buffer1 = malloc(10);
	char *buffer2 = malloc(10);
	
	ft_read(0, buffer1, 10);
	int length1 = ft_strlen(buffer1);
	printf("Length 1: %d\n", length1);
	
	ft_read(0, buffer2, 10);
	int length2 = ft_strlen(buffer2);
	printf("Length 2: %d\n", length2);

	ft_write(1, buffer1, ft_strlen(buffer1));
	ft_write(1, buffer2, ft_strlen(buffer2));
	
	int cmp = ft_strcmp(buffer1, buffer2);
	if (!cmp)
		printf("IGUALES\n");
	else
		printf("Comparacion: %i\n", cmp);

	return 0;
}
