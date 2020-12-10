/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:42:02 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/10 01:00:08 by rprieto-         ###   ########.fr       */
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
	t_error_info error_info;
	t_program_params program_params;

	save_img = false;
	init_error_struct(&error_info);
	
	if (check_arguments(&error_info, &save_img, argc, argv) && check_file(&error_info, &program_params, argv[1]))
	{
		main_raycast(program_params);
	}
	else
	{
		print_error(&error_info);
	}
	return (0);
}

//Returns false if it finds an error and true if not
t_bool		check_arguments(t_error_info *error_info, t_bool *save_img, int argc, char **argv)
{
	if (argc == 1)
		return (raise_error(error_info, missing_argument_error));
	else
	{
		//--save argument
		if (argc == 3)
		{
			if (ft_strlen(argv[2]) == 6 && !ft_strncmp(argv[2], "--save", 6))
				*save_img = true;
			else
				return (raise_error(error_info, second_arg_error));
		}
		//file argument
		if (ft_strlen(argv[1]) <= 4)
			return (raise_error(error_info, wrong_filename_error));
		else if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
			return (raise_error(error_info, wrong_extension_error));
	}
	return (true);
}
