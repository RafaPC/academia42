/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_index_of.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:24:45 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/30 20:17:14 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_get_index_of(char *string, char c)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == c)
			return (index);
		index++;
	}
	return (-1);
}
