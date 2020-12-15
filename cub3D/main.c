/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/15 12:50:54 by rprieto-         ###   ########.fr       */
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
	init_texture(vars->mlx.mlx, vars->textureN, program_params.path_NO_texture);
	init_texture(vars->mlx.mlx, vars->textureS, program_params.path_SO_texture);
	init_texture(vars->mlx.mlx, vars->textureE, program_params.path_EA_texture);
	init_texture(vars->mlx.mlx, vars->textureW, program_params.path_WE_texture);
	init_texture(vars->mlx.mlx, vars->textureSprite, program_params.path_sprite_texture);
}

void	init(t_vars *vars, t_program_params program_params)
{
	int sizex, sizey;
	vars->mlx.mlx = mlx_init();
	mlx_get_screen_size(vars->mlx.mlx, &sizex, &sizey);
	vars->screen_width = (sizex < program_params.resolution_x) ? sizex : program_params.resolution_x;
	vars->screen_height = (sizey < program_params.resolution_y) ? sizey : program_params.resolution_y;
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, vars->screen_width, vars->screen_height, "Cub3D");
	//IMAGE
	vars->mlx.img = (t_data*)malloc(sizeof(t_data));
	vars->mlx.img->img = mlx_new_image(vars->mlx.mlx, vars->screen_width, vars->screen_height);
	vars->mlx.img->addr = mlx_get_data_addr(vars->mlx.img->img, &vars->mlx.img->bits_per_pixel, &vars->mlx.img->line_length, &vars->mlx.img->endian);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
	//COLOR
	vars->ceiling_color = program_params.ceilling_color;
	vars->floor_color = program_params.floor_color;
	//POSITION
	vars->player_vars.px = program_params.player_x + 0.5;
	vars->player_vars.py = program_params.player_y + 0.5;
	vars->player_vars.pangle = program_params.player_angle;
	vars->player_vars.pdx = cos(vars->player_vars.pangle);
	vars->player_vars.pdy = sin(vars->player_vars.pangle);
	vars->wall_face = 1;
	vars->keys_pressed.w = false;
	vars->keys_pressed.a = false;
	vars->keys_pressed.s = false;
	vars->keys_pressed.d = false;
	vars->keys_pressed.left_arrow = false;
	vars->keys_pressed.right_arrow = false;
	vars->map = program_params.map;
	vars->distances = (float*)malloc(vars->screen_width * sizeof(float));
	init_textures(vars, program_params);

	vars->sprite = NULL;
}

void		main_raycast(t_program_params program_params)
{
	t_vars			vars;
	init(&vars, program_params);
	mlx_hook(vars.mlx.win, 2, 1L<<0, on_key_pressed, &vars.keys_pressed);
	mlx_hook(vars.mlx.win, 3, 1L<<1, on_key_released, &vars.keys_pressed);
	mlx_hook(vars.mlx.win, 07, 1L<<4, on_window_enter, &vars);
	mlx_hook(vars.mlx.win, 17, 0L, on_window_closed, &vars);
	mlx_loop_hook(vars.mlx.mlx, render_screen, &vars);
	render_screen(&vars);
	mlx_loop(vars.mlx.mlx);
}