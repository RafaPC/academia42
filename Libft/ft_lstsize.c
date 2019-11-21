/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:46:41 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/21 16:41:13 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*lst_elem;

	size = 0;
	lst_elem = lst->next;
	while (lst_elem)
	{
		lst_elem = lst_elem->next;
		size++;
	}
	return (size);
}
