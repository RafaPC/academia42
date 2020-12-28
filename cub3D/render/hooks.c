/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/27 12:25:19 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdio.h>

int		on_key_pressed(int keycode, t_vars *vars)
{
	t_keys	*keys_pressed;

	keys_pressed = &vars->keys_pressed;
	if (keycode == 65307)
	{
		on_window_closed(vars);
		return (0);
	}
	if (keycode == 'a')
		keys_pressed->a = true;
	if (keycode == 'd')
		keys_pressed->d = true;
	if (keycode == 'w')
		keys_pressed->w = true;
	if (keycode == 's')
		keys_pressed->s = true;
	if (keycode == 65361)
		keys_pressed->left_arrow = true;
	if (keycode == 65363)
		keys_pressed->right_arrow = true;
	if (keycode == 65362)
		keys_pressed->up_arrow = true;
	if (keycode == 65364)
		keys_pressed->down_arrow = true;
	return (0);
}

int		on_key_released(int keycode, t_keys *keys_pressed)
{
	if (keycode == 'a')
		keys_pressed->a = false;
	if (keycode == 'd')
		keys_pressed->d = false;
	if (keycode == 'w')
		keys_pressed->w = false;
	if (keycode == 's')
		keys_pressed->s = false;
	if (keycode == 65361)
		keys_pressed->left_arrow = false;
	if (keycode == 65363)
		keys_pressed->right_arrow = false;
	if (keycode == 65362)
		keys_pressed->up_arrow = false;
	if (keycode == 65364)
		keys_pressed->down_arrow = false;
	return (0);
}

/*
** TODO: funcion que se trigeree cuando se vuelva a entrar a la ventana
*/

int		on_window_enter(t_vars *vars)
{
	return (0);
}

int		on_window_closed(t_vars *vars)
{
	free_memory(vars);
	exit(0);
	return (0);
}
