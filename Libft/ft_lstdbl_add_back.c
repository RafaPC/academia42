/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbl_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:37:56 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/20 00:38:07 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdbl_add_back(t_list_dbl **lst, t_list_dbl *new)
{
	t_list_dbl	*p;

	p = *lst;
	if (!p)
		*lst = new;
	else
	{
		p = ft_lstdbl_last(p);
		p->next = new;
		p->next->prev = p;
	}
}
