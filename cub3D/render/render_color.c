/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:16:04 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/12 15:20:01 by rprieto-         ###   ########.fr       */
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

	image = vars->textureN;
	x_texture = (int)(image->width * vars->texture_x);
	y_texture = (int)(image->height * (0.5 + (0.5 * y / column_size)));
	return (get_pixel(image->data, x_texture, y_texture));
}

unsigned int get_image_colour_MIO(t_vars *vars, int column_size, float y, int y_offset)
{
	t_texture texture;
	int x_texture;
	int y_texture;

	if (vars->wall_face == south_face)
		texture = *vars->textureS;
	else if (vars->wall_face == north_face)
		texture = *vars->textureN;
	else if (vars->wall_face == east_face)
		texture = *vars->textureE;
	else if (vars->wall_face == west_face)
		texture = *vars->textureW;
	//X and Y position of the texture
	x_texture = (int)(texture.width * vars->texture_x);
	if (y_offset > 0)
		y_texture = (int)((texture.height * y));
	else
		y_texture = (int)((texture.height * y));
	// if (y_texture > texture.height)
	// 	y_texture = texture.height;
	// else if (y_texture < 0)
	// 	y_texture = 0;
	return (get_pixel(texture.data, x_texture, y_texture));
}