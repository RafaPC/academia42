/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/06 13:52:32 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>
#include <math.h>
#include "../../printf/ft_printf.h"

int offset_column = 0;
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		render_screen(t_vars *vars)
{
	offset_column = 0;
	int green = create_trgb(0, 0, 255, 0);
	int blue = create_trgb(0, 200, 150, 200);
	mlx_destroy_image(vars->mlx, vars->img->img);
	vars->img->img = mlx_new_image(vars->mlx, 1300, 600);
	check_movement(vars);
	// draw_fov(vars, green);
	raycast(vars);
	draw_map(vars);
	draw_line(vars, (vars->px * 40) + vars->pdx * 40, (vars->py * 40) - vars->pdy * 20, blue);
	display_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

void	display_player(t_vars *vars)
{
	int color;

	color = create_trgb(0, 255, 0, 0);
	draw_square(5, 5, vars->px * 40, vars->py * 40, color, vars);
}

void	display_vars(t_vars *vars)
{
	int color;
	
	color = create_trgb(0, 0, 255, 0);
	mlx_string_put(vars->mlx, vars->win, 700, 50, color, "hola");
}

void	draw_square(int width, int height, int xpos, int ypos, int color, t_vars *vars)
{
	int x, y;
	x = 0;
	y = 0;
	while (x < width)
	{
		while (y < height)
		{
			my_mlx_pixel_put(vars->img, xpos + x, ypos + y, color);
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

	xincrement = (xend - (vars->px * 40)) / 30;
	yincrement = (yend - (vars->py * 40)) / 30;
	while (i < length)
	{
		my_mlx_pixel_put(vars->img, (vars->px * 40) + (xincrement * i), (vars->py * 40) + (yincrement * i), color);
		i++;
	}
}

void	draw_fov(t_vars *vars, int color)
{
	float i = vars->pangle - PI/3;
	if (i < 0)
		i += 2 * PI;
	for (int j = 0; j < 20; j++)
	{
		i += 0.1;
		if (i > 2 * PI)
			i -= 2 * PI;
		draw_line(vars, ((vars->px * 40) + cos(i) * 50), ((vars->py * 40) - sin(i) * 50), color);
	}
}

void	draw_map(t_vars *vars)
{
	int x, y;
	x = 0;
	y = 0;
	int wall_color = create_trgb(0, 255, 255, 255);
	int space_color = create_trgb(0, 50, 50, 50);
	int	map[8][8] =
	{
		{1,1,1,1,1,1,1,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	while (y < 8)
	{
		while (x < 8)
		{
			// if (map[y][x] == 1)
			// 	draw_square(40, 40, (x * 40) + 2 * x, (y * 40) + 2 * y, wall_color, vars);
			// else if (map[y][x] == 0)
			// 	draw_square(40, 40, (x * 40) + 2 * x, (y * 40) + 2 * y, space_color, vars);
			if (map[y][x] == 1)
				draw_square(40, 40, (x * 40), (y * 40), wall_color, vars);
			else if (map[y][x] == 0)
				draw_square(40, 40, (x * 40), (y * 40), space_color, vars);			
			x++;
		}
		y++;
		x = 0;
	}
}

void	render_column(t_vars *vars, float distance)
{
	int column_height;
	int color;

	column_height = (8 * 90)/distance;
	if (column_height > 600 || column_height < 0)
		column_height = 599;
	else if (column_height < 30)
		column_height = 30;
	if (vars->wall_face == north_face || vars->wall_face == south_face)
		color = create_trgb(0, 100, 200, (vars->wall_face == north_face) ? 255 : 80);
	else if (vars->wall_face == west_face || vars->wall_face == east_face)
		color = create_trgb(0, 200, (vars->wall_face == east_face) ? 255 : 80, 100);
	color = add_shade(distance / 9, color);
	draw_square(1, column_height, offset_column, 300 -(column_height/2), color, vars);
	offset_column += 1;
}
