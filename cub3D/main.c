/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/30 20:09:02 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>
#include <X11/X.h>
#include "libft.h"
#include "ft_printf.h"

/*
**		Receives a texture struct and initialices the data in it
*/

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

/*
**		Inicialices all the textures
*/

int		init_textures(void *mlx, t_textures *textures, t_program_params params)
{
	if (!init_texture(mlx, &textures->wall_north, params.path_NO_texture))
		return (0);
	if (!init_texture(mlx, &textures->wall_south, params.path_SO_texture))
		return (0);
	if (!init_texture(mlx, &textures->wall_east, params.path_EA_texture))
		return (0);
	if (!init_texture(mlx, &textures->wall_west, params.path_WE_texture))
		return (0);
	if (!init_texture(mlx, &textures->sprite_1, params.path_sprite_texture))
		return (0);
	if (!init_texture(mlx, &textures->sprite_2, params.path_sprite2_texture))
		return (0);
	if (!init_texture(mlx, &textures->sprite_3, params.path_sprite3_texture))
		return (0);
	return (1);
}

/*
**		Shrinks the window size if the parameters are bigger than the screen
*/

void	set_window_size(t_vars *vars, int window_width, int window_height)
{
	int screen_width;
	int screen_height;

	mlx_get_screen_size(vars->mlx.mlx, &screen_width, &screen_height);
	if (screen_width < window_width)
	{
		vars->window_width = screen_width;
		ft_printf("Window width will be shrinked to screen width\n");
	}
	else
		vars->window_width = window_width;
	if (screen_height < window_height)
	{
		vars->window_height = screen_height;
		ft_printf("Window height will be shrinked to screen height\n");
	}
	else
		vars->window_height = window_height;
}	

/*
**		TODO:
*/

void	init(t_vars *vars, t_program_params program_params)
{
	vars->mlx.mlx = mlx_init();
	vars->mlx.win = NULL;
	set_window_size(vars, program_params.window_width, program_params.window_height);
	vars->mlx.img = (t_data*)malloc(sizeof(t_data));
	vars->mlx.img->img = mlx_new_image(vars->mlx.mlx, vars->window_width, vars->window_height);
	vars->mlx.img->addr = mlx_get_data_addr(vars->mlx.img->img, &vars->mlx.img->bits_per_pixel, &vars->mlx.img->line_length, &vars->mlx.img->endian);
	if (!init_textures(vars->mlx.mlx, &vars->textures, program_params))
	{
		ft_printf("Fail to initialice a texture\n");
		// free_memory(vars);
		exit(0);
	}

	free(program_params.path_NO_texture);
	free(program_params.path_SO_texture);
	free(program_params.path_EA_texture);
	free(program_params.path_WE_texture);
	free(program_params.path_sprite_texture);
	free(program_params.path_sprite2_texture);
	free(program_params.path_sprite3_texture);
	vars->distances = (float*)malloc(vars->window_width * sizeof(float));
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
	vars->keys_pressed.up_arrow = false;
	vars->keys_pressed.down_arrow = false;
	vars->keys_pressed.left_arrow = false;
	vars->keys_pressed.right_arrow = false;
	vars->keys_pressed.mouse_moved = false;
	vars->mouse_x = 1;
	vars->mouse_y = 1;
	vars->map = program_params.map;
	vars->sprite = NULL;
	vars->max_col_height = vars->window_width / (tanf(FOV / 2 ) * 2);
	vars->y_offset = 0;
	vars->score = 0;
}

/*
**		TODO:
*/

void	main_raycast(t_program_params program_params, t_bool save_img)
{
	t_vars			vars;

	init(&vars, program_params);
	if (save_img)
	{
		raycast(&vars);
		render_sprites(&vars);
		take_screenshot(*vars.mlx.img, vars);
		free_and_close(&vars);
	}
	else
	{
		vars.mlx.win = mlx_new_window(vars.mlx.mlx, vars.window_width, vars.window_height, "Cub3D");
		mlx_put_image_to_window(vars.mlx.mlx, vars.mlx.win, vars.mlx.img->img, 0, 0);
		raycast(&vars);
		render_sprites(&vars);
		mlx_put_image_to_window(
			vars.mlx.mlx, vars.mlx.win, vars.mlx.img->img, 0, 0);
		// mlx_mouse_hide(vars.mlx.mlx, vars.mlx.win);
		mlx_hook(vars.mlx.win, KeyPress, KeyPressMask, on_key_pressed, &vars);
		mlx_hook(vars.mlx.win, KeyRelease, KeyReleaseMask, on_key_released, &vars.keys_pressed);
		mlx_hook(vars.mlx.win, FocusIn, FocusChangeMask, on_window_focused, &vars);
		mlx_hook(vars.mlx.win, ClientMessage, NoEventMask, on_window_closed, &vars);
		mlx_loop_hook(vars.mlx.mlx, render_screen, &vars);
		mlx_loop(vars.mlx.mlx);
	}
}