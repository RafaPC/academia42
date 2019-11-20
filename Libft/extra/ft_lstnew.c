/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:40:23 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/20 18:31:56 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_list		ft_lstnew(void const *content)
{
	t_list *new_elem;

	new_elem = (t_list*)malloc(sizeof(t_list));
	new_elem->content = content;
	new_elem->next = NULL;
}
