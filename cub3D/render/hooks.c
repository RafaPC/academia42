/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/18 16:16:57 by rprieto-         ###   ########.fr       */
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
		exit(0);
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
	mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	mlx_destroy_display(vars->mlx.mlx);
	exit(0);
	return (0);
}
