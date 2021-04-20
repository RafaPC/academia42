/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbl_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:38:21 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/20 00:38:31 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_dbl	*ft_lstdbl_last(t_list_dbl *lst)
{
	if (lst == 0)
		return (lst);
	else
		while (lst->next != 0)
			lst = lst->next;
	return (lst);
}
