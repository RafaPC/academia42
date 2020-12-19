/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:42:02 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/19 00:48:12 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int		main(int argc, char const *argv[])
{
	//TODO: hacer todo esto en una función que no sea el main puede estar guay
	//porque simplemente hago return cuando algo salga mal y ya está
	//Puede ser tipo return(add_error(&error_info, tipo_error))
	t_bool	save_img;
	t_program_params program_params;

	save_img = false;
	
	if (check_arguments(&save_img, argc, (char**)argv) && check_file(&program_params, argv[1]))
	{
		main_raycast(program_params);
	}
	else
	{
		//TODO:Maybe liberar memoria del program params
	}
	return (0);
}

//Returns false if it finds an error and true if not
t_bool		check_arguments(t_bool *save_img, int argc, char **argv)
{
	if (argc == 1)
		return (print_error("Falta argumento"));
	else
	{
		//--save argument
		if (argc == 3)
		{
			if (ft_strlen(argv[2]) == 6 && !ft_strncmp(argv[2], "--save", 6))
				*save_img = true;
			else
				return (print_error("Segundo argumento mal escrito"));
		}
		//file argument
		if (ft_strlen(argv[1]) <= 4)
			return (print_error("El nombre del archivo dado por argumento no es correcto"));
		else if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
			return (print_error("El archivo dado por argumento tiene la extensión errónea"));
	}
	return (true);
}
