/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/11 03:10:06 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>
#include "libft.h"
#include <stdio.h>

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
	mlx_destroy_image(vars->mlx.mlx, vars->mlx.img->img);
	vars->mlx.img->img = mlx_new_image(vars->mlx.mlx, vars->screen_width, vars->screen_height);
	check_movement(vars);
	raycast(vars);
	draw_map(vars);
	display_player(vars);
	display_vars(vars);
	
	render_sprites(vars);

	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
	return (0);
}

void	display_player(t_vars *vars)
{
	int color;

	color = create_trgb(0, 255, 0, 0);
	draw_square(5, 5, vars->player_vars.px * 10, vars->player_vars.py * 10, color, vars);
}

void	display_vars(t_vars *vars)
{
	int color;
	
	color = create_trgb(0, 0, 255, 0);
	mlx_string_put(vars->mlx.mlx, vars->mlx.win, vars->screen_width - 100, 50, color, "hola");
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
		draw_line(vars, ((vars->player_vars.px * 40) + cos(i) * 50),
		((vars->player_vars.py * 40) - sin(i) * 50), color);
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

void	render_column(t_vars *vars, float distance)
{
	int column_height;
	int ceil_color;
	int floor_color;

	ceil_color = create_trgb(0, 102, 217, 255);
	floor_color = create_trgb(0, 51, 153, 51);
	//Calculate column height based on the distance to the wall
	column_height = (8 * 90)/distance;
	int real_column_height = column_height;
	//Check column limits
	if (column_height > vars->screen_height)
		column_height = vars->screen_height;
	else if (column_height < 30)
		column_height = 30;
	//Dibuja techo y suelo
	if (column_height < vars->screen_height)
	{
		draw_square(1, (vars->screen_height - column_height)/2, offset_column, 0, ceil_color, vars);
		draw_square(1, (vars->screen_height - column_height)/2, offset_column, (vars->screen_height / 2) + (column_height / 2), floor_color, vars);
		//Esto era para poner el suelo más "arriba" más oscuro
		// for (int i = 300 + (column_height / 2); i < 600; i++)
		// 	my_mlx_pixel_put(vars->img, offset_column, i, add_shade((float)(600 - i/700), floor_color));
	}
	//Forma mía
	int drawStart = vars->screen_height / 2;
	int color_text;
	//El pixel en la mitad de la pantalla en el eje Y
	color_text = get_wall_color(vars, vars->texture_x, 0.5);
	my_mlx_pixel_put(vars->mlx.img, offset_column, drawStart, color_text);
	for (float i = 1; (int)i <= column_height/2; i++)
	{
		//Mitad superior
		color_text = get_wall_color(vars, vars->texture_x, (real_column_height/2 - i)/real_column_height);
		my_mlx_pixel_put(vars->mlx.img, offset_column, (int)(drawStart - i), color_text);
		//Mitad inferior
		color_text = get_wall_color(vars, vars->texture_x, (real_column_height/2 + i)/real_column_height);
		my_mlx_pixel_put(vars->mlx.img, offset_column, (int)(drawStart + i), color_text);
	}
	debug = 1;
	offset_column += 1;
}

unsigned int    get_pixel(t_data *image, int x, int y)
{
    unsigned int	*dst;

    dst = (unsigned int*)(image->addr + (y * image->line_length + (x * (image->bits_per_pixel / 8))));
    return (*(dst));
}

void	render_sprites(t_vars *vars)
{
	t_list		*sprite_elem;
	t_sprite	sprite;

	order_sprites(vars->sprite);
	sprite_elem = vars->sprite;
	while (sprite_elem)
	{
		sprite = *(t_sprite*)sprite_elem->content;
		sprite.size_half = (vars->screen_height / 2) / sprite.distance;
		sprite.center_x = (tanf(sprite.angle) / tanf(FOV / 2) + 1) * vars->screen_width / 2;
		sprite.center_y = vars->screen_height / 2 + (vars->screen_height / 2) / sprite.distance - sprite.size_half * 0.75;
		draw_sprite(vars, sprite);
		sprite_elem = sprite_elem->next;
	}
	ft_lstclear(&vars->sprite, free);
}

int get_sprite_colour(t_vars *vars, int x, int y, t_sprite sprite)
{
    t_texture *image;
    float image_x;
    float image_y;

    image = vars->textureSprite;
    image_x = ((x - sprite.center_x + sprite.size_half) / (float)sprite.size_half / 2) * image->width;
    image_y = (y / ((float)sprite.size_half * 2)) * image->height;
    return (get_pixel(image->data, image_x, image_y));
}

void	draw_sprite_column(int drawing_position, t_sprite sprite, t_vars *vars)
{
	int y_draw_coord;
    int y_position;
    int size;
    int pixel;

    size = sprite.size_half * 2;
    y_position = 0;
    y_draw_coord = sprite.center_y - sprite.size_half;
    while (y_draw_coord < 0)
    {
        y_position++;
        y_draw_coord++;
    }
    while (y_position < size && y_draw_coord < vars->screen_height)
    {
        pixel = get_sprite_colour(vars, drawing_position, y_position, sprite);
        // pixel = create_trgb(0, 255, 0, 0);
		if (pixel != -16777216)
            my_mlx_pixel_put(vars->mlx.img, drawing_position, y_draw_coord, pixel);
        y_position++;
        y_draw_coord++;
    }
}

void	draw_sprite(t_vars *vars, t_sprite sprite)
{
	int column_position;

	column_position = sprite.center_x - sprite.size_half > 0 ? sprite.center_x - sprite.size_half : 0;
	
	while (column_position < sprite.center_x  + sprite.size_half && column_position < vars->screen_width)
	{
		if (vars->distances[column_position] > sprite.distance)
			draw_sprite_column(column_position, sprite, vars);
		column_position++;
	}
}

