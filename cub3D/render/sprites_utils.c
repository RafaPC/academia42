/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:40:31 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/11 03:07:11 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "libft.h"

//AQuí podría pasarle player_vars y el puntero al sprite por separado
void	add_sprite_coords(float x, float y, t_vars *vars)
{
	t_list		*sprite_elem;
	t_sprite	*sprite;

	x += 0.5;
	y += 0.5;
	sprite_elem = vars->sprite;
	//Checkear que no se repiten x e y
	while (sprite_elem != NULL)
	{
		sprite = (t_sprite*)sprite_elem->content;
		//Si ya hay un sprite con esos valores, se sale
		if (sprite->x == x && sprite->y == y)
			return ;
		sprite_elem = sprite_elem->next;
	}
	if (!(sprite = (t_sprite*)malloc(sizeof(t_sprite))))
		return ;
	sprite->x = x;
	sprite->y = y;
	// x = fabsf(vars->px - x);
	// y = fabsf(vars->py - y);
	x = sprite->x - vars->player_vars.px;
	y = -(sprite->y - vars->player_vars.py);
	sprite->angle = vars->player_vars.pangle - atanf(y / x);
	sprite->distance = sqrtf(x * x + y * y) * fabsf(cosf(sprite->angle));
	ft_lstadd_front(&vars->sprite, ft_lstnew(sprite));
}

void	ft_lstmove_backwards(t_list *list)
{
	void *aux;

	if (list->next)
	{
		aux = list->content;
		list->content = list->next->content;
		list->next->content = aux;
	}
}

void    order_sprites(t_list *sprite)
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
            if (aux->next && ((t_sprite *)aux->next->content)->distance > ((t_sprite *)aux->content)->distance)
            {
                ft_lstmove_backwards(aux);
                changed = true;
            }
            aux = aux->next;
        }
    }  
}   