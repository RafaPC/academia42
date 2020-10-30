/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/30 20:40:33 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>
#include "../../printf/ft_printf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		render_screen(t_vars *vars)
{
		display_player(vars);
		draw_map(vars);
		return (0);
}

void	display_player(t_vars *vars)
{
	int i, j;
	int color;

	i = 0;
	j = 0;
	color = create_trgb(0, 255, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img->img);
	vars->img->img = mlx_new_image(vars->mlx, 800, 800);
	draw_square(40, 40, vars->px, vars->py, color, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
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

void	draw_map(t_vars *vars)
{
	int x, y;
	x = 0;
	y = 0;
	int wall_color = create_trgb(0, 0, 255, 255);
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
	// vars->map = map;
	// ft_printf("llega");
	static int cosa = 0;
	if (!cosa++)
		ft_printf("%i", map[0][0]);
	// ft_printf("%i", map[0][0]);
	while (y < 8)
	{
		while (x < 8)
		{
			if (map[y][x] == 1)
				draw_square(40, 40, x * 40, y * 40, wall_color, vars);
			x++;
		}
		y++;
		x = 0;
	}
}
