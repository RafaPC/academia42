/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/15 12:50:12 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>

int offset_column = 0;
static int debug = 0;
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		render_screen(t_vars *vars)
{
	debug = 0;
	offset_column = 0;
	int blue = create_trgb(0, 200, 150, 200);
	mlx_destroy_image(vars->mlx, vars->img->img);
	vars->img->img = mlx_new_image(vars->mlx, 1920, 1080);
	check_movement(vars);
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
	int ceil_color;
	int floor_color;
	int screen_width;
	int screen_height;

	screen_width = 1920;
	screen_height = 1080;
	ceil_color = create_trgb(0, 102, 217, 255);
	floor_color = create_trgb(0, 51, 153, 51);
	//Calculate column height based on the distance to the wall
	column_height = (int)(8 * 90)/distance;
	//Check column limits
	if (column_height > screen_height)
		column_height = screen_height;
	// else if (column_height < 30)
	// 	column_height = 30;
	//Dibuja techo y suelo
	if (column_height < screen_height)
	{
		draw_square(1, (screen_height - column_height)/2, offset_column, 0, ceil_color, vars);
		draw_square(1, (screen_height - column_height)/2, offset_column, (screen_height / 2) + (column_height / 2), floor_color, vars);
		//Esto era para poner el suelo más "arriba" más oscuro
		// for (int i = 300 + (column_height / 2); i < 600; i++)
		// 	my_mlx_pixel_put(vars->img, offset_column, i, add_shade((float)(600 - i/700), floor_color));
	}
		//Forma mía
		int drawStart = screen_height / 2;
		int drawEnd = column_height / 2;
		int color_text;
		int diferencia = (8 * 90)/distance;
		for (float i = 0; (int)i <= drawEnd; i++)
		{
			//-----------DEBUG
			// double x = (i - drawStart) / column_height;
			// if (!debug)
			// {
			// 	printf("i:%i\n", i);
			// 	printf("column height:%i\n", column_height);
			// 	printf("Valor de y(entre 0 y 1): %f\n", x);
			// }
			// color_text = get_pixel(texture.data, (int)(texture.width * vars->texture_x),
			// (int)(texture.height * ((i - drawStart) / column_height)));
			// column_height = (8 * 90)/distance;
			color_text = get_image_colour(vars, column_height, i, diferencia);
			my_mlx_pixel_put(vars->img, offset_column, drawStart + (int)i, color_text);
			color_text = get_image_colour(vars, column_height, -i, diferencia);
			my_mlx_pixel_put(vars->img, offset_column, drawStart - (int)i, color_text);
		}
		debug = 1;
	offset_column += 1;
}

void	render_column_MIO(t_vars *vars, float distance)
{
	int column_height;
	int color;
	int ceil_color;
	int floor_color;
	int screen_width;
	int screen_height;

	screen_width = 1920;
	screen_height = 1080;
	ceil_color = create_trgb(0, 102, 217, 255);
	floor_color = create_trgb(0, 51, 153, 51);
	//Calculate column height based on the distance to the wall
	column_height = (8 * 90)/distance;
	//Check column limits
	if (column_height > screen_height)
		column_height = screen_height;
	else if (column_height < 30)
		column_height = 30;
	//Dibuja techo y suelo
	if (column_height < screen_height)
	{
		draw_square(1, (screen_height - column_height)/2, offset_column, 0, ceil_color, vars);
		draw_square(1, (screen_height - column_height)/2, offset_column, (screen_height / 2) + (column_height / 2), floor_color, vars);
		//Esto era para poner el suelo más "arriba" más oscuro
		// for (int i = 300 + (column_height / 2); i < 600; i++)
		// 	my_mlx_pixel_put(vars->img, offset_column, i, add_shade((float)(600 - i/700), floor_color));
	}
	//Forma mía
	int drawStart = screen_height / 2 - column_height / 2;
	int drawEnd = drawStart + column_height;
	int color_text;
	for (float i = drawStart; (int)i <= drawEnd; i++)
	{
		color_text = create_trgb(0, 255, 70, 70);
		color_text = get_image_colour_MIO(vars, (i - drawStart)/column_height);
		my_mlx_pixel_put(vars->img, offset_column, (int)i, color_text);
	}
	debug = 1;
	offset_column += 1;
}
unsigned int    get_pixel(t_data *image, int x, int y)
{
    unsigned int	*dst;

    dst = image->addr + (y * image->line_length + (x * (image->bits_per_pixel / 8)));
    return (*(dst));
}
