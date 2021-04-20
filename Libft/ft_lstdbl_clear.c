/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbl_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:39:15 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/20 19:30:19 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdbl_clear(t_list_dbl **lst, void (*del)(void *))
{
	t_list_dbl		*aux;

	if (lst == NULL || *lst == NULL)
		return ;
	while ((*lst)->prev)
		*lst = (*lst)->prev;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdbl_delone(*lst, del);
		*lst = aux;
	}
}
