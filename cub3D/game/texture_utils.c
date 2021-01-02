/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:16:04 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/02 11:44:50 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	Receives a struct of texturas and a variable that indicates
**	which wall is facing
*/

int	get_wall_color(t_textures textures, t_wall_face wall_face,
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
**	Recieves a texture and two floats (one per axis) with values
**	from 0.0 to 1.0
**	It takes the pixel corresponding to the coordinates given
**	(0, 0) would be the top left corner of the texture
**	(0, 1) would be the bottom right corner of the texture
*/

int	get_image_color(t_texture texture, float x, float y)
{
	int x_texture;
	int y_texture;

	x_texture = (int)(texture.width * x);
	y_texture = (int)(texture.height * y);
	return (get_pixel(texture.data, x_texture, y_texture));
}
