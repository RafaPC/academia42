/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/10 01:00:25 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>

void init_texture(void *mlx, t_texture *text, char *file)
{
	text->data = (t_data*)malloc(sizeof(t_data));
	text->data->img = mlx_xpm_file_to_image(mlx, file, &text->width, &text->height);
	text->data->addr = mlx_get_data_addr(text->data->img, &text->data->bits_per_pixel, &text->data->line_length, &text->data->endian);
}

void	init_textures(t_vars *vars, t_program_params program_params)
{
	vars->textureN = (t_texture*)malloc(sizeof(t_texture));
	vars->textureS = (t_texture*)malloc(sizeof(t_texture));
	vars->textureE = (t_texture*)malloc(sizeof(t_texture));
	vars->textureW = (t_texture*)malloc(sizeof(t_texture));
	vars->textureSprite = (t_texture*)malloc(sizeof(t_texture));

	//Checkear si se abren bien y se inicializan
	init_texture(vars->mlx, vars->textureN, program_params.path_NO_texture);
	init_texture(vars->mlx, vars->textureS, program_params.path_SO_texture);
	init_texture(vars->mlx, vars->textureE, program_params.path_EA_texture);
	init_texture(vars->mlx, vars->textureW, program_params.path_WE_texture);
	init_texture(vars->mlx, vars->textureSprite, program_params.path_sprite_texture);
}

void	init(t_vars *vars, t_program_params program_params)
{
	int sizex, sizey;
	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &sizex, &sizey);
	vars->screen_width = (sizex < program_params.resolution_x) ? sizex : program_params.resolution_x;
	vars->screen_height = (sizey < program_params.resolution_y) ? sizey : program_params.resolution_y;
	vars->win = mlx_new_window(vars->mlx, vars->screen_width, vars->screen_height, "Hello world");
	//IMAGE
	vars->img = (t_data*)malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(vars->mlx, vars->screen_width, vars->screen_height);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel, &vars->img->line_length, &vars->img->endian);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	//POSITION
	vars->px = program_params.player_x + 0.5;
	vars->py = program_params.player_y + 0.5;
	vars->pangle = program_params.player_angle;
	vars->pdx = cos(vars->pangle);
	vars->pdy = sin(vars->pangle);
	vars->wall_face = 1;
	vars->keys_pressed.w = false;
	vars->keys_pressed.a = false;
	vars->keys_pressed.s = false;
	vars->keys_pressed.d = false;
	vars->map = program_params.map;
	init_textures(vars, program_params);

	vars->sprite = NULL;
}

void		main_raycast(t_program_params program_params)
{
	t_vars			vars;
	init(&vars, program_params);
	mlx_hook(vars.win, 2, 1L<<0, on_key_pressed, &vars);
	mlx_hook(vars.win, 3, 1L<<1, on_key_released, &vars);
	mlx_loop_hook(vars.mlx, render_screen, &vars);
	render_screen(&vars);
	mlx_loop(vars.mlx);
}