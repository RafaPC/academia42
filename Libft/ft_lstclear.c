/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:38:47 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/22 12:54:11 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_aux1;
	t_list	*lst_aux2;

	lst_aux1 = (*lst);
	lst_aux2 = lst_aux1->next;
	while (lst_aux1)
	{
		del(lst_aux1);
		free(lst_aux1);
		lst_aux1 = lst_aux2;
		lst_aux2 = lst_aux1->next;
	}
	lst = NULL;
}
