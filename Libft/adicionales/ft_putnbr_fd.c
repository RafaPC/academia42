/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:24:48 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/20 13:08:36 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long int	n_copy;
	char		c;

	/*
	if (nb == -2147483648)
		write(1, "-2147483648", 12);
	*/
	n_copy = n;
	if (n < 0)
	{
		n_copy = -n;
		write(fd, "-", 1);
	}
	if (n_copy > 9)
	{
		ft_putnbr_fd(n_copy / 10, fd);
		ft_putchar_fd(n_copy % 10 + 48, fd);
	}
	else
		ft_putchar_fd(n_copy + 48, fd);
}

int main(int argc, char const *argv[])
{
	int fd = open("test.txt", O_WRONLY);
	ft_putnbr_fd(-99, fd);
	return 0;
}
