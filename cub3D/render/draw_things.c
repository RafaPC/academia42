/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:27:55 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/16 01:03:07 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_square(t_coords coords, int color, t_data *img)
{
	int x;
	int y;

	x = coords.start_x;
	while (x <= coords.end_x)
	{
		y = coords.start_y;
		while (y <= coords.end_y)
		{
			my_mlx_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_square_length(t_coords coords, int color, t_data *img)
{
	int x;
	int y;

	x = coords.start_x;
	while (x <= coords.end_x)
	{
		y = coords.start_y;
		while (y <= coords.end_y)
		{
			my_mlx_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_line(t_vars *vars, float xend, float yend, int color)
{
	int length = 60;
	int i = 0;
	float xincrement;
	float yincrement;

	xincrement = (xend - (vars->player_vars.px * 40)) / 30;
	yincrement = (yend - (vars->player_vars.py * 40)) / 30;
	while (i < length)
	{
		my_mlx_pixel_put(vars->mlx.img, (vars->player_vars.px * 40) + (xincrement * i),
		(vars->player_vars.py * 40) + (yincrement * i), color);
		i++;
	}
}

void	draw_map(t_vars *vars)
{
	int x;
	int y;
	int color;

	int wall_color = create_trgb(0, 255, 255, 255);
	int space_color = create_trgb(0, 50, 50, 50);
	int sprite_color = create_trgb(0, 220, 50, 100);

	y = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			if (vars->map[y][x] == '2')
				color = sprite_color;
			else if (vars->map[y][x] == '1')
				color = wall_color;
			else if (vars->map[y][x] == '0')
				color = space_color;
			if (vars->map[y][x] != ' ')
				draw_square(
				get_coords_struct(x * 10, y * 10, x * 10 + 10, y * 10 + 10),
				color, vars->mlx.img);	
			x++;
		}
		y++;
	}
}

void	draw_player(t_vars *vars)
{
	int color;
	int x;
	int y;

	x = vars->player_vars.px * 10;
	y = vars->player_vars.py * 10;
	color = create_trgb(0, 255, 0, 0);
	draw_square(
	get_coords_struct(x, y, x + 5, y + 5), color, vars->mlx.img);
}

t_coords	get_coords_struct(int x_start, int y_start, int x_end, int y_end)
{
	t_coords coords;

	coords.start_x = x_start;
	coords.start_y = y_start;
	coords.end_x = x_end;
	coords.end_y = y_end;
	return (coords);
}
