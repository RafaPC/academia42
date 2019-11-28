/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:51:34 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/26 16:49:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst_last;

	if (!alst)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		lst_last = ft_lstlast(*alst);
		lst_last->next = new;
	}
}
