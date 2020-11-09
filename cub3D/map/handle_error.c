/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:30:32 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/08 16:38:03 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdio.h>

void		init_error_struct(t_error_info *error_info)
{
	error_info->error_type = 0;
	error_info->error_row = 0;
	error_info->error_column = 0;
}

t_bool		print_error(t_error_info *error_info)
{
	//Here reads the error type and prints it
	printf("Error!");
	return (false);
}

