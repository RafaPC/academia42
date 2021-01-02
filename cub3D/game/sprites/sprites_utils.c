/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:40:31 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/02 15:29:45 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "libft.h"

/*
**		Receives a pointer to a sprite and other arguments with info
**		to calculate the distance to the sprite, its coordinates
*/

void	calculate_sprite_info(t_sprite *sprite, t_player_vars player,
t_vars vars)
{
	float y;
	float x;
	float sprite_angle;
	float height_adjustment;

	x = sprite->x - player.x;
	y = -(sprite->y - player.y);
	sprite_angle = player.angle - atanf(y / x);
	sprite->distance = sqrtf(x * x + y * y) * fabsf(cosf(sprite_angle));
	sprite->size_half = ((vars.max_col_height + vars.window_width) / 4)
	/ sprite->distance;
	height_adjustment = vars.window_width - vars.window_height;
	sprite->center_y = vars.window_height / 2 + vars.y_offset +
	(vars.window_height / 2) / sprite->distance - sprite->size_half * 0.75;
	if (vars.keys_pressed.left_ctrl)
		sprite->center_y -= (vars.max_col_height / 6) / (sprite->distance * 3);
	sprite->center_y += (height_adjustment / 2) / sprite->distance;
	sprite->center_x = (tanf(sprite_angle) / tanf(FOV / 2) + 1) *
		vars.window_width / 2;
}

void	add_sprite_coords(float x, float y, t_vars *vars, t_texture texture)
{
	t_list		*sprite_elem;
	t_sprite	*sprite;

	sprite_elem = vars->sprite;
	while (sprite_elem != NULL)
	{
		sprite = (t_sprite*)sprite_elem->content;
		if (sprite->x == x && sprite->y == y)
			return ;
		sprite_elem = sprite_elem->next;
	}
	if (!(sprite = (t_sprite*)malloc(sizeof(t_sprite))))
		return ;
	sprite->texture = texture;
	sprite->x = x;
	sprite->y = y;
	calculate_sprite_info(sprite, vars->player, *vars);
	ft_lstadd_front(&vars->sprite, ft_lstnew(sprite));
}

void	order_sprites(t_list *sprite)
{
	t_list *aux;
	t_bool changed;

	changed = true;
	while (changed)
	{
		changed = false;
		aux = sprite;
		while (aux)
		{
			if (aux->next && ((t_sprite *)aux->next->content)->distance >
			((t_sprite *)aux->content)->distance)
			{
				ft_lstmove_backwards(aux);
				changed = true;
			}
			aux = aux->next;
		}
	}
}
