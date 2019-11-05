void	ft_bzero(void *s, unsigned int n)
{
	int i;

	i = 0;
	while(i < n)
		((char*)s)[i++] = 0;
}
