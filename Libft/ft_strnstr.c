/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   haystacknhaystack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:41:48 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/05 16:53:51 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	*ft_strnstr(const char *haystack, const char *needle)
{
	//TODO: en realidad es el strstr, así que habría que añadirle
	//la variable de longitud pero ya tiene 25 líneass :D
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	if (!needle[i])
		return (haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = i + 1;
			k = 1;
			while (haystack[j] == needle[k])
			{
				j++;
				k++;
				if (!needle[k])
					return (&haystack[i]);
			}
		}
		i++;
	}
	return (0);
}
