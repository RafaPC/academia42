/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/03 17:08:54 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include "../printf/ft_printf.h"
#include <math.h>
#include <stdio.h>

void	init(t_vars *vars)
{
	vars->img = (t_data*)malloc(sizeof(t_data));
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1600, 800, "Hello world");
	vars->img->img = mlx_new_image(vars->mlx, 1600, 800);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel, &vars->img->line_length, &vars->img->endian);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	vars->px = 6.3;
	vars->py = 4.3;
	vars->pangle = PI/4;
	vars->pdx = cos(vars->pangle);
	vars->pdy = sin(vars->pangle);
	// display_vars(vars);
}

int		main(int argc, char const *argv[])
{
	t_error_info	*error_info; 
	t_vars			vars;

	init(&vars);
	// vars.map[8][8] = 
	// [
	// 	[1,1,1,1,1,1,1,1],
	// 	[1,0,1,0,0,0,0,1],
	// 	[1,0,1,0,0,0,0,1],
	// 	[1,0,1,0,0,0,0,1],
	// 	[1,0,0,0,0,0,0,1],
	// 	[1,0,0,0,0,1,0,1],
	// 	[1,0,0,0,0,0,0,1],
	// 	[1,1,1,1,1,1,1,1]
	// ];
	mlx_hook(vars.win, 2, 1L<<0, on_key_pressed, &vars);
	render_screen(&vars);
	// mlx_loop_hook(vars.mlx, render_screen, &vars);
	mlx_loop(vars.mlx);
	
	// save_img = false;
	// // if (argc == 3)
	// // {
	// // 	if (ft_strncmp(argv[1], "--save", 6))
	// // 		save_img = true;
	// // }
	// if (argc > 1)
	// {
	// 	char	*file = (char*)argv[1];
	// 	check_map(error_info, file);
	// }
	return (0);
}