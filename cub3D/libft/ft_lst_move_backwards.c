/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_move_backwards.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:24:24 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/16 12:25:57 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmove_backwards(t_list *lst)
{
	void *aux;

	if (lst->next)
	{
		aux = lst->content;
		lst->content = lst->next->content;
		lst->next->content = aux;
	}
}
