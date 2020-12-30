/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:03:24 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/30 18:44:03 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**		Order the sprites from further to closer and
**		iterates rendering all of them
*/

void	render_sprites(t_vars *vars)
{
	t_list		*sprite_elem;
	t_sprite	sprite;

	order_sprites(vars->sprite);
	sprite_elem = vars->sprite;
	while (sprite_elem)
	{
		sprite = *(t_sprite*)sprite_elem->content;
		draw_sprite(*vars, sprite);
		sprite_elem = sprite_elem->next;
	}
	ft_lstclear(&vars->sprite, free);
}

/*
**		Receives a sprite and draws it
*/

void	draw_sprite(t_vars vars, t_sprite sprite)
{
	int column_position;

	if (sprite.center_x - sprite.size_half > 0)
		column_position = sprite.center_x - sprite.size_half;
	else
		column_position = 0;
	while (column_position < (sprite.center_x + sprite.size_half) &&
	column_position < vars.window_width)
	{
		if (vars.distances[column_position] > sprite.distance)
			draw_sprite_column(vars, sprite, column_position);
		column_position++;
	}
}

/*
**		Draws one column of a sprite
*/

void	draw_sprite_column(t_vars vars, t_sprite sprite, int drawing_position)
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
	while (y_position < size && y_draw_coord < vars.window_height)
	{
		pixel = get_image_color(sprite.texture,
		(drawing_position - sprite.center_x +
		sprite.size_half) / (float)sprite.size_half / 2,
		y_position / ((float)sprite.size_half * 2));
		if (get_t(pixel) != 255 && pixel != 0)
			my_mlx_pixel_put(vars.mlx.img, drawing_position,
			y_draw_coord, pixel);
		y_position++;
		y_draw_coord++;
	}
}
