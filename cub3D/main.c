/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/21 16:00:53 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int		main(int argc, char const *argv[])
{
	t_error_info	*error_info;
	t_bool			save_img;

	save_img = false;
	// if (argc == 3)
	// {
	// 	if (ft_strncmp(argv[1], "--save", 6))
	// 		save_img = true;
	// }
	char	*file = (char*)argv[1];
	check_map(error_info, file);
	return (0);
}
