/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:53:54 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/26 17:53:26 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*begin;

	if (!lst)
		return (NULL);
	tmp = lst;
	if (!(begin = ft_lstnew(f(tmp->content))))
		return (NULL);
	tmp = tmp->next;
	while (tmp)
	{
		if (!(new = ft_lstnew(f(tmp->content))))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, new);
		tmp = tmp->next;
	}
	return (begin);
}
