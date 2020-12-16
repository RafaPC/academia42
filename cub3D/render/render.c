/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/16 01:47:11 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>
#include "libft.h"
#include <stdio.h>

int		render_screen(t_vars *vars)
{
	mlx_destroy_image(vars->mlx.mlx, vars->mlx.img->img);
	vars->mlx.img->img =
	mlx_new_image(vars->mlx.mlx, vars->screen_width, vars->screen_height);
	check_movement(vars);
	raycast(vars);
	draw_map(vars);
	draw_player(vars);
	render_sprites(vars);
	mlx_put_image_to_window(
	vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
	display_vars(vars);
	return (0);
}

void	display_vars(t_vars *vars)
{
	int color;

	color = create_trgb(0, 0, 255, 0);
	mlx_string_put(
	vars->mlx.mlx, vars->mlx.win, vars->screen_width - 100, 50, color, "hola");
}

int		get_column_height(t_vars vars, float distance)
{
	int column_height;

	column_height = (8 * 90) / distance;
	if (column_height > vars.screen_height)
		column_height = vars.screen_height;
	else if (column_height < 30)
		column_height = 30;
	return (column_height);
}

void	render_column(t_vars *vars, float distance, float wall_x,
int x_coord)
{
	int		column_height;
	int		color_text;
	int		real_column_height;
	float	i;
	int		draw_start;

	real_column_height = (8 * 90) / distance;
	i = 1;
	draw_start = vars->screen_height / 2;
	column_height = get_column_height(*vars, distance);
	if (column_height < vars->screen_height)
		render_ceil_and_floor(vars, x_coord, column_height);
	color_text = get_wall_color(vars, wall_x, 0.5);
	my_mlx_pixel_put(vars->mlx.img, x_coord, draw_start, color_text);
	while ((int)i <= column_height / 2)
	{
		color_text = get_wall_color(
			vars, wall_x, (real_column_height / 2 - i) / real_column_height);
		my_mlx_pixel_put(vars->mlx.img, x_coord, draw_start - i, color_text);
		color_text = get_wall_color(
			vars, wall_x, (real_column_height / 2 + i) / real_column_height);
		my_mlx_pixel_put(vars->mlx.img, x_coord, draw_start + i, color_text);
		i++;
	}
}

void	render_ceil_and_floor(t_vars *vars, int x_coord, int column_height)
{
	draw_square(get_coords_struct(x_coord, 0, x_coord,
		vars->screen_height / 2 - column_height / 2),
		vars->ceiling_color, vars->mlx.img);
	draw_square(get_coords_struct(x_coord,
		vars->screen_height / 2 + column_height / 2,
		x_coord, vars->screen_height),
		vars->floor_color, vars->mlx.img);
}
