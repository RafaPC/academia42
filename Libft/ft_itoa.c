/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:24:49 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/30 21:00:52 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_nbr(char *string, unsigned int index, long int number)
{
	if (number >= 10)
	{
		fill_nbr(string, index - 1, number / 10);
		string[index] = (number % 10) + 48;
	}
	else
		string[index] = number + 48;
}

char	*ft_itoa(int n)
{
	char			*string;
	long int		n_copy;
	unsigned int	digits;
	unsigned int	index;

	if (n == 0)
		return (ft_strdup("0"));
	digits = ft_nbrlen(n);
	n_copy = n;
	index = digits - 1;
	string = (char *)malloc((digits + 1) * sizeof(char));
	if (!string)
		return (NULL);
	if (n_copy < 0)
	{
		string[0] = '-';
		n_copy = -n_copy;
	}
	fill_nbr(string, index, n_copy);
	string[digits] = '\0';
	return (string);
}
