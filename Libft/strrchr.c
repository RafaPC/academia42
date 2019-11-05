/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:50:14 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/05 13:27:14 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int last_ocurrence;

	i = 0;
	last_ocurrence = -1;
	while(s[i])
	{
		if(s[i] == c)
		{
			last_ocurrence = i;
		}
		i++;
	}
	if(c == '\0')
		return (&s[i]);
	return (last_ocurrence != -1) ? (s[last_ocurrence]) : (0);
}
