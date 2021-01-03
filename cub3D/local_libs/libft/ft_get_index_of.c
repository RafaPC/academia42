/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_index_of.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:24:45 by rprieto-          #+#    #+#             */
/*   Updated: 2019/12/02 13:13:51 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_get_index_of(char *string, char c)
{
	int index;

	index = 0;
	while (string[index])
	{
		if (string[index] == c)
			return (index);
		index++;
	}
	return (-1);
}
