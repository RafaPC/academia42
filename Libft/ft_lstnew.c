/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:40:23 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/25 15:37:32 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		ft_lstnew(void const *content)
{
	t_list *new_elem;

	if (!(new_elem = (t_list*)malloc(sizeof(t_list))))
		return (*new_elem);
	new_elem->content = (void*)content;
	new_elem->next = NULL;
	return (*new_elem);
}
