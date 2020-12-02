/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/02 19:24:56 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>
#include <stdio.h>

void init_texture(void *mlx, t_texture *text, char *file)
{
	text->data = (t_data*)malloc(sizeof(t_data));
	text->data->img = mlx_xpm_file_to_image(mlx, file, &text->width, &text->height);
	text->data->addr = mlx_get_data_addr(text->data->img, &text->data->bits_per_pixel, &text->data->line_length, &text->data->endian);
}

void	init_textures(t_vars *vars)
{
	vars->textureN = (t_texture*)malloc(sizeof(t_texture));
	vars->textureS = (t_texture*)malloc(sizeof(t_texture));
	vars->textureE = (t_texture*)malloc(sizeof(t_texture));
	vars->textureW = (t_texture*)malloc(sizeof(t_texture));
	vars->textureSprite = (t_texture*)malloc(sizeof(t_texture));

	init_texture(vars->mlx, vars->textureN, "./textures/sand.XPM");
	init_texture(vars->mlx, vars->textureS, "./textures/stone_brick.XPM");
	init_texture(vars->mlx, vars->textureE, "./textures/wood.XPM");
	init_texture(vars->mlx, vars->textureW, "./textures/brick.XPM");
	init_texture(vars->mlx, vars->textureW, "./textures/brick.XPM");
	init_texture(vars->mlx, vars->textureSprite, "./textures/barrel.xpm");
}

void	init(t_vars *vars)
{

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 800, 800, "Hello world");
	//IMAGE
	vars->img = (t_data*)malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(vars->mlx, 800, 800);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel, &vars->img->line_length, &vars->img->endian);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	//POSITION
	vars->px = 6.5;
	vars->py = 6.5;
	// vars->pangle = PI/4;
	// vars->pangle = 72.333911 * 180/PI;
	// vars->pangle = 1.26 + (PI/2)/3;
	// vars->pangle = 90 * 180/PI;
	vars->pangle = PI/2;
	vars->pdx = cos(vars->pangle);
	vars->pdy = sin(vars->pangle);
	vars->wall_face = 1;
	vars->keys_pressed.w = false;
	vars->keys_pressed.a = false;
	vars->keys_pressed.s = false;
	vars->keys_pressed.d = false;
	init_textures(vars);

	vars->sprite = NULL;
}

int		main(void)
{
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
	// render_screen(&vars);
	mlx_loop(vars.mlx);
	return (0);
}