/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:54:00 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/21 17:41:38 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		size;
	t_list	*lst_elem;
	t_list	*last_elem;

	lst_elem = lst->next;
	last_elem = lst;
	while (lst_elem)
	{
		last_elem = lst_elem;
		lst_elem = lst_elem->next;
	}
	return (last_elem);
}
