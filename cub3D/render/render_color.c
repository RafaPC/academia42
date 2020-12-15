/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:16:04 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/15 12:30:07 by rprieto-         ###   ########.fr       */
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

unsigned int get_image_color(t_texture texture, float x, float y)
{
	int x_texture;
	int y_texture;

	//X and Y position of the texture
	x_texture = (int)(texture.width * x);
	y_texture = (int)(texture.height * y);
	return (get_pixel(texture.data, x_texture, y_texture));
}

unsigned int get_wall_color(t_vars *vars, float x, float y)
{
	t_texture texture;

	if (vars->wall_face == south_face)
		texture = *vars->textureS;
	else if (vars->wall_face == north_face)
		texture = *vars->textureN;
	else if (vars->wall_face == east_face)
		texture = *vars->textureE;
	else if (vars->wall_face == west_face)
		texture = *vars->textureW;
	return (get_image_color(texture, x, y));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

unsigned int    get_pixel(t_data *image, int x, int y)
{
    unsigned int	*dst;

    dst = (unsigned int*)(image->addr + (y * image->line_length + (x * (image->bits_per_pixel / 8))));
    return (*(dst));
}
