/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:42:02 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/21 12:45:35 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int		main(int argc, char const *argv[])
{
	t_bool	save_img;
	t_program_params program_params;

	save_img = false;
	initialice_program_params(&program_params);
	if (check_arguments(&save_img, argc, (char**)argv) && check_file(&program_params, argv[1]))
	{
		main_raycast(program_params, save_img);
	}
	else
	{
		if (program_params.path_NO_texture)
			free(program_params.path_NO_texture);
		if (program_params.path_SO_texture)
			free(program_params.path_SO_texture);
		if (program_params.path_EA_texture)
			free(program_params.path_EA_texture);
		if (program_params.path_WE_texture)
			free(program_params.path_WE_texture);
		if (program_params.path_sprite_texture)
			free(program_params.path_sprite_texture);
		if (program_params.map)
			free_map(program_params.map);
	}
	return (0);
}

/*
** Returns false if it finds an error and true if not
*/

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
		if (ft_strlen(argv[1]) <= 4)
			return (print_error("El nombre del archivo dado por argumento no es correcto"));
		else if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
			return (print_error("El archivo dado por argumento tiene la extensión errónea"));
	}
	return (true);
}
