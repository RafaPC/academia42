/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:30:32 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/10 17:36:08 by rprieto-         ###   ########.fr       */
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
	if (error_info->error_type == missing_argument_error)
		printf("Falta argumento");
	else if (error_info->error_type == too_many_args_error)
		printf("Hay demasiados argumentos");
	else if (error_info->error_type == second_arg_error)
		printf("Segundo argumento mal escrito");
	else if (error_info->error_type == wrong_filename_error)
		printf("El nombre del archivo dado por argumento no es correcto");
	else if (error_info->error_type == wrong_extension_error)
		printf("El archivo dado por argumento tiene la extensión errónea");
	else
		printf("Error indefinido");
	return (false);
}

void *	raise_error(t_error_info *error_info, t_error_type error_id)
{
	error_info->error_type = error_id;
	return (NULL);
}
