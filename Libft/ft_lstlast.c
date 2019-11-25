/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:54:00 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/22 12:42:01 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_elem;

	last_elem = lst;
	lst = lst->next;
	while (lst)
	{
		last_elem = lst;
		lst = lst->next;
	}
	return (last_elem);
}
