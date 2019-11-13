/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:05:06 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/13 17:42:48 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_calloc(unsigned int count, unsigned int size)
{
	char *array;

	if ((int)count <= 0 || (int)size <= 0)
		array = malloc(count * size);
	if (!array)
		return (0);
		//TODO: podria declarar  NULL como variable de precompilacion
	bzero(array, count);
	return (array);
}

int		main(int argc, char const *argv[])
{
	ft_calloc(5, sizeof(char));
	return (0);
}
