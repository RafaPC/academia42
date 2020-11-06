/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/06 19:05:02 by rprieto-         ###   ########.fr       */
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
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "Hello world");
	vars->img->img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel, &vars->img->line_length, &vars->img->endian);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	vars->px = 1.3;
	vars->py = 6.8;
	// vars->pangle = PI/4;
	// vars->pangle = 72.333911 * 180/PI;
	// vars->pangle = 1.26 + (PI/2)/3;
	vars->pangle = 1.26;
	vars->pdx = cos(vars->pangle);
	vars->pdy = sin(vars->pangle);
	vars->wall_face = 1;
	vars->keys_pressed.w = false;
	vars->keys_pressed.a = false;
	vars->keys_pressed.s = false;
	vars->keys_pressed.d = false;
	vars->texture.data = mlx_xpm_file_to_image(vars->mlx, "./tree_texture.xpm", &vars->texture.width, &vars->texture.height);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->texture.data, 30, 30);
	// display_vars(vars);
}

int		main(int argc, char const *argv[])
{
	t_error_info	*error_info; 
	t_vars			vars;
	//Floor
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
	mlx_hook(vars.win, 3, 1L<<1, on_key_released, &vars);
	mlx_loop_hook(vars.mlx, render_screen, &vars);
	mlx_loop(vars.mlx);
	// render_screen(&vars);

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