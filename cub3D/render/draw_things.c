/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:27:55 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/14 15:46:23 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_square(int width, int height, int xpos, int ypos, int color, t_vars *vars)
{
	int x, y;
	x = 0;
	y = 0;
	while (x < width)
	{
		while (y < height)
		{
			my_mlx_pixel_put(vars->mlx.img, xpos + x, ypos + y, color);
			y++;
		}
		x++;
		y = 0;
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

void	draw_fov(t_vars *vars, int color)
{
	float i = vars->player_vars.pangle - PI/3;
	if (i < 0)
		i += 2 * PI;
	for (int j = 0; j < 20; j++)
	{
		i += 0.1;
		if (i > 2 * PI)
			i -= 2 * PI;
		draw_line(vars, ((vars->player_vars.px * 40) + cosf(i) * 50),
		((vars->player_vars.py * 40) - sinf(i) * 50), color);
	}
}

void	draw_map(t_vars *vars)
{
	int x, y;
	
	y = 0;
	int wall_color = create_trgb(0, 255, 255, 255);
	int space_color = create_trgb(0, 50, 50, 50);
	int sprite_color = create_trgb(0, 220, 50, 100);
	int color = space_color;
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
				draw_square(10, 10, (x * 10), (y * 10), color, vars);	
			x++;
		}
		y++;
	}
}

void	draw_player(t_vars *vars)
{
	int color;

	color = create_trgb(0, 255, 0, 0);
	draw_square(5, 5, vars->player_vars.px * 10, vars->player_vars.py * 10, color, vars);
}
