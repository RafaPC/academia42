/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:16:04 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/30 16:29:12 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <math.h>

/*
**	Receives a distance and a color and returns the color
**	as darker as longer the distance
*/

int		add_shade(float distance, int color)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	distance /= 30;
	r = r - (r * distance);
	g = g - (g * distance);
	b = b - (b * distance);
	return (create_trgb(get_t(color), r, g, b));
}

/*
**		Recieves a texture and two floats (one per axis) with values
**		from 0.0 to 1.0
**		It takes the pixel corresponding to the coordinates given
**		(0, 0) would be the top left corner of the texture
**		(0, 1) would be the bottom right corner of the texture
*/

int		get_image_color(t_texture texture, float x, float y)
{
	int x_texture;
	int y_texture;

	x_texture = (int)(texture.width * x);
	y_texture = (int)(texture.height * y);
	return (get_pixel(texture.data, x_texture, y_texture));
}

/*
**		Receives a struct of texturas and a variable that indicates
**		which wall is facing
*/

int		get_wall_color(t_textures textures, t_wall_face wall_face,
float x, float y)
{
	t_texture texture;

	if (wall_face == north_face)
		texture = textures.wall_north;
	else if (wall_face == south_face)
		texture = textures.wall_south;
	else if (wall_face == east_face)
		texture = textures.wall_east;
	else if (wall_face == west_face)
		texture = textures.wall_east;
	return (get_image_color(texture, x, y));
}

/*
**		Receives coordinates, a pointer to an image data and a pixel
**		It places the pixel in the img data at the coordinates
*/

void	my_mlx_pixel_put(t_data *image_data, int x, int y, int pixel)
{
	char	*dst;

	dst = image_data->addr +
	(y * image_data->line_length + x * (image_data->bits_per_pixel / 8));
	*(int*)dst = pixel;
}

/*
**		Receives an image data and coordinates
**		It returns the pixel in the image data at the coordinates
*/

int		get_pixel(t_data image_data, int x, int y)
{
	int	pixel;

	pixel = *(int*)(image_data.addr +
	(y * image_data.line_length + (x * (image_data.bits_per_pixel / 8))));
	return (pixel);
}
