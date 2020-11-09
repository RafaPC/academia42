/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:42:02 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/09 12:52:20 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "cub3d.h"
#include <stdio.h>

int		main(int argc, char const *argv[])
{
	t_bool	save_img;
	t_error_info error_info;

	save_img = false;
	init_error_struct(&error_info);
	// error_info = (t_error_info*)malloc(sizeof(t_error_info));
	if (argc == 1)
	{
		error_info.error_type = missing_argument_error;
	}
	else
	{
		//--save argument
		if (argc == 3)
		{
			if (!ft_strncmp(argv[2], "--save", 6))
				save_img = true;
			else
				error_info.error_type = second_arg_error;
		}
		//file argument
		char	*file = (char*)argv[1];
		printf("%s", file);
		if (argc > 1)
		{
			// check_map(error_info, file);
		}
	}

	if (error_info.error_type)
		print_error(&error_info);
	else
	{
		//Aquí empezar el raycasting y eso
	}
	return (0);
}