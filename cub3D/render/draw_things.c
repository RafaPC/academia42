/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:27:55 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/16 17:35:51 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void		draw_square(t_coords coords, int color, t_data *img)
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

void		draw_map(t_vars *vars)
{
	int x;
	int y;
	int color;

	y = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			if (vars->map[y][x] == '1')
				color = WALL_COLOR;
			else if (vars->map[y][x] == '0')
				color = SPACE_COLOR;
			if (vars->map[y][x] != ' ')
				draw_square(
				get_coords_struct(x * 10, y * 10, x * 10 + 10, y * 10 + 10),
				color, vars->mlx.img);
			x++;
		}
		y++;
	}
}

void		draw_player(t_vars *vars)
{
	int color;
	int x;
	int y;

	x = vars->player.x * 10;
	y = vars->player.y * 10;
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
