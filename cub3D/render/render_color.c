/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:16:04 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/11 11:05:49 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <math.h>

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}

int		get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}

int		get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int		add_shade(double distance, int color)
{
	int r, g, b;
	r = get_r(color);
	g = get_g(color);
	b = get_b(color);

	if (distance > 1)
		distance = 1;
	r = r - (r * distance);
	g = g - (g * distance);
	b = b - (b * distance);
	return (create_trgb(get_t(color), r, g, b));
}

unsigned int get_image_colour(t_vars *vars, int column_size, int y)
{
	t_texture *image;
	int x_texture;
	int y_texture;

	image = vars->texture;
	x_texture = (int)(image->width * vars->texture_x);
	y_texture = (int)(image->height * (0.5 + (0.5 * y / column_size)));
	return (get_pixel(image->data, x_texture, y_texture));
}

unsigned int get_image_colour_MIO(t_vars *vars, int column_size, float y)
{
	t_texture *image;
	int x_texture;
	int y_texture;

	image = vars->texture;
	x_texture = (int)(image->width * vars->texture_x);
	// y_texture = (int)(image->height * (0.5 + (0.5 * y / column_size)));
	y_texture = (int)((image->height * y));
	if (y_texture > image->height)
		y_texture = image->height;
	else if (y_texture < 0)
		y_texture = 0;
	return (get_pixel(image->data, x_texture, y_texture));
}