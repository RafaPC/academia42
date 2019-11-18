/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:05:06 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/15 12:11:43 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	*ft_calloc(unsigned int count, unsigned int size)
{
	char *array;

	if ((int)count <= 0 || (int)size <= 0)
		if(!(array = malloc(count * size)))
			return (NULL);
	//TODO: podria declarar  NULL como variable de precompilacion
	bzero(array, count);
	return (array);
}

int		main(int argc, char const *argv[])
{
	ft_calloc(5, sizeof(char));
	return (0);
}
