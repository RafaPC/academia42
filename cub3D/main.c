/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/18 18:35:07 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>

int		init_texture(void *mlx, t_texture *text, char *file)
{
	text->data.img = mlx_xpm_file_to_image(
		mlx, file, &text->width, &text->height);
	if (text->data.img == NULL)
		return (0);
	text->data.addr = mlx_get_data_addr(text->data.img,
		&text->data.bits_per_pixel,
		&text->data.line_length,
		&text->data.endian);
	return (1);
}

int		init_textures(t_vars *vars, t_program_params program_params)
{
	if (!init_texture(vars->mlx.mlx, &vars->textureN, program_params.path_NO_texture))
		return (0);
	if (!init_texture(vars->mlx.mlx, &vars->textureS, program_params.path_SO_texture))
		return (0);
	if (!init_texture(vars->mlx.mlx, &vars->textureE, program_params.path_EA_texture))
		return (0);
	if (!init_texture(vars->mlx.mlx, &vars->textureW, program_params.path_WE_texture))
		return (0);
	if (!init_texture(vars->mlx.mlx, &vars->textureSprite,
		program_params.path_sprite_texture))
		return (0);
	return (1);
}

void	check_window_size(t_vars *vars, int resolution_x, int resolution_y)
{
	int size_x;
	int size_y;

	mlx_get_screen_size(vars->mlx.mlx, &size_x, &size_y);
	vars->screen_width = (size_x < resolution_x) ? size_x : resolution_x;
	vars->screen_height = (size_y < resolution_y) ? size_y : resolution_y;
}

void	init(t_vars *vars, t_program_params program_params)
{
	vars->mlx.mlx = mlx_init();
	check_window_size(vars, program_params.resolution_x, program_params.resolution_y);
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, vars->screen_width, vars->screen_height, "Cub3D");
	vars->mlx.img = (t_data*)malloc(sizeof(t_data));
	vars->mlx.img->img = mlx_new_image(vars->mlx.mlx, vars->screen_width, vars->screen_height);
	vars->mlx.img->addr = mlx_get_data_addr(vars->mlx.img->img, &vars->mlx.img->bits_per_pixel, &vars->mlx.img->line_length, &vars->mlx.img->endian);
	init_textures(vars, program_params);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
	vars->distances = (float*)malloc(vars->screen_width * sizeof(float));

	free(program_params.path_NO_texture);
	free(program_params.path_SO_texture);
	free(program_params.path_EA_texture);
	free(program_params.path_WE_texture);
	free(program_params.path_sprite_texture);

	vars->ceiling_color = program_params.ceilling_color;
	vars->floor_color = program_params.floor_color;
	vars->player.x = program_params.player_x + 0.5;
	vars->player.y = program_params.player_y + 0.5;
	vars->player.angle = program_params.player_angle;
	vars->player.dx = cosf(vars->player.angle);
	vars->player.dy = sinf(vars->player.angle);
	vars->keys_pressed.w = false;
	vars->keys_pressed.a = false;
	vars->keys_pressed.s = false;
	vars->keys_pressed.d = false;
	vars->keys_pressed.left_arrow = false;
	vars->keys_pressed.right_arrow = false;
	vars->map = program_params.map;
	vars->sprite = NULL;
}

void		main_raycast(t_program_params program_params)
{
	t_vars			vars;
	init(&vars, program_params);
	mlx_hook(vars.mlx.win, 2, 1L<<0, on_key_pressed, &vars);
	mlx_hook(vars.mlx.win, 3, 1L<<1, on_key_released, &vars.keys_pressed);
	// mlx_hook(vars.mlx.win, 07, 1L<<4, on_window_enter, &vars);
	mlx_hook(vars.mlx.win, 17, 0L, on_window_closed, &vars);
	mlx_loop_hook(vars.mlx.mlx, render_screen, &vars);
	mlx_loop(vars.mlx.mlx);
}