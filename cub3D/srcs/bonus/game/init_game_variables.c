/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:49:18 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 21:14:37 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "cub3d.h"

/*
**		Initialices all the pointers to NULL
*/

void	init_to_null(t_vars *vars)
{
	vars->mlx.mlx = NULL;
	vars->mlx.win = NULL;
	vars->mlx.img = NULL;
	vars->distances = NULL;
	vars->textures.wall_north.data.img = NULL;
	vars->textures.wall_south.data.img = NULL;
	vars->textures.wall_west.data.img = NULL;
	vars->textures.wall_east.data.img = NULL;
	vars->textures.sprite_1.data.img = NULL;
	vars->textures.sprite_2.data.img = NULL;
	vars->textures.sprite_3.data.img = NULL;
	vars->sprite = NULL;
}

/*
**		Initialices variables needed
*/

t_bool	init_game_variables(t_vars *vars, t_program_params params)
{
	vars->map = params.map;
	if (!(vars->mlx.mlx = mlx_init()))
		return (print_error("Failed to initialice mlx variable"));
	vars->mlx.win = NULL;
	set_window_size(vars, params.window_width, params.window_height);
	if (!(vars->mlx.img = (t_data*)malloc(sizeof(t_data))))
		return (print_error("Failed to allocate memory"));
	if (!(vars->mlx.img->img = mlx_new_image(vars->mlx.mlx, vars->window_width,
	vars->window_height)))
		return (print_error("Failed to initialice mlx variable"));
	vars->mlx.img->addr = mlx_get_data_addr(vars->mlx.img->img,
		&vars->mlx.img->bits_per_pixel, &vars->mlx.img->line_length,
		&vars->mlx.img->endian);
	if (!init_textures(vars->mlx.mlx, &vars->textures, params))
		return (false);
	if (!(vars->distances = (float*)malloc(vars->window_width * sizeof(float))))
		return (print_error("Failed to allocate memory"));
	init_game_variables2(vars, params);
	return (true);
}

/*
**		Initialices more variables needed
*/

void	init_game_variables2(t_vars *vars, t_program_params params)
{
	vars->ceiling_color = params.ceilling_color;
	vars->floor_color = params.floor_color;
	vars->player.x = params.player_x + 0.5;
	vars->player.y = params.player_y + 0.5;
	vars->player.angle = params.player_angle;
	vars->player.dx = cosf(vars->player.angle);
	vars->player.dy = sinf(vars->player.angle);
	vars->keys_pressed.w = false;
	vars->keys_pressed.a = false;
	vars->keys_pressed.s = false;
	vars->keys_pressed.d = false;
	vars->keys_pressed.up_arrow = false;
	vars->keys_pressed.down_arrow = false;
	vars->keys_pressed.left_arrow = false;
	vars->keys_pressed.right_arrow = false;
	vars->keys_pressed.left_ctrl = false;
	vars->mouse_x = 1;
	vars->mouse_y = 1;
	vars->max_col_height = vars->window_width /
	(tanf(FOV / 2) * 2);
	vars->y_offset = 0;
	vars->score = 0;
}

/*
**		Receives a texture struct and initialices the data in it
*/

t_bool	init_texture(void *mlx, t_texture *text, char *file)
{
	text->data.img = mlx_xpm_file_to_image(
		mlx, file, &text->width, &text->height);
	if (text->data.img == NULL)
		return (print_error_texture(file));
	text->data.addr = mlx_get_data_addr(text->data.img,
		&text->data.bits_per_pixel,
		&text->data.line_length,
		&text->data.endian);
	return (true);
}

/*
**		Inicialices all the textures
*/

t_bool	init_textures(void *mlx, t_textures *textures,
t_program_params params)
{
	if (!init_texture(mlx, &textures->wall_north, params.path_north_texture))
		return (false);
	if (!init_texture(mlx, &textures->wall_south, params.path_south_texture))
		return (false);
	if (!init_texture(mlx, &textures->wall_east, params.path_east_texture))
		return (false);
	if (!init_texture(mlx, &textures->wall_west, params.path_west_texture))
		return (false);
	if (!init_texture(mlx, &textures->sprite_1, params.path_sprite_texture))
		return (false);
	if (!init_texture(mlx, &textures->sprite_2, params.path_sprite2_texture))
		return (false);
	if (!init_texture(mlx, &textures->sprite_3, params.path_sprite3_texture))
		return (false);
	return (true);
}
