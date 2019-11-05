/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:28:47 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/05 13:26:54 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (c == '\0') ? (&s[i]) : (0);
}

int		main(void)
{
	char test[] = "holaaeaea";
	char *puntero = strchr(test, 'r');
	printf("%s", puntero);
	return (1);
}
