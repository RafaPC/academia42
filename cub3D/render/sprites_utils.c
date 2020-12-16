/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:40:31 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/16 12:49:03 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "libft.h"

/*
** //TODO:Aquí podría pasarle player_vars y el puntero al sprite por separado
*/

void	add_sprite_coords(float x, float y, t_vars *vars)
{
	t_list		*sprite_elem;
	t_sprite	*sprite;

	x += 0.5;
	y += 0.5;
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
	sprite->x = x;
	sprite->y = y;
	x = sprite->x - vars->player.x;
	y = -(sprite->y - vars->player.y);
	sprite->angle = vars->player.angle - atanf(y / x);
	sprite->distance = sqrtf(x * x + y * y) * fabsf(cosf(sprite->angle));
	sprite->size_half = (vars->screen_height / 2) / sprite->distance;
	sprite->center_y = vars->screen_height / 2 + (vars->screen_height / 2) /
		sprite->distance - sprite->size_half * 0.75;
	sprite->center_x = (tanf(sprite->angle) / tanf(FOV / 2) + 1) *
		vars->screen_width / 2;
	ft_lstadd_front(&vars->sprite, ft_lstnew(sprite));
}

/*
** TODO: Meter esto a la libft
*/

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
