/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/31 17:10:06 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

/*
**	Function called whenever a key is pressed
**	Sets to true whichever key it's been pressed
**	If the pressed key is the Escape Key
**	calls the funcion that close the program
*/

int	on_key_pressed(int keycode, t_vars *vars)
{
	t_keys	*keys_pressed;

	keys_pressed = &vars->keys_pressed;
	if (keycode == ESC_KEY)
	{
		free_and_close(vars);
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
	if (keycode == ARROW_LEFT_KEY)
		keys_pressed->left_arrow = true;
	if (keycode == ARROW_RIGHT_KEY)
		keys_pressed->right_arrow = true;
	if (keycode == ARROW_UP_KEY)
		keys_pressed->up_arrow = true;
	if (keycode == ARROW_DOWN_KEY)
		keys_pressed->down_arrow = true;
	return (0);
}

/*
**	Function called whenever a key is released
**	Sets to false whichever key it's been released
*/

int	on_key_released(int keycode, t_keys *keys_pressed)
{
	if (keycode == 'a')
		keys_pressed->a = false;
	if (keycode == 'd')
		keys_pressed->d = false;
	if (keycode == 'w')
		keys_pressed->w = false;
	if (keycode == 's')
		keys_pressed->s = false;
	if (keycode == ARROW_LEFT_KEY)
		keys_pressed->left_arrow = false;
	if (keycode == ARROW_RIGHT_KEY)
		keys_pressed->right_arrow = false;
	if (keycode == ARROW_UP_KEY)
		keys_pressed->up_arrow = false;
	if (keycode == ARROW_DOWN_KEY)
		keys_pressed->down_arrow = false;
	return (0);
}

/*
**	Function called when the windows is reopened
**	Redraws the screen
*/

int	on_window_focused(t_vars *vars)
{
	raycast(vars);
	render_sprites(vars);
	mlx_put_image_to_window(
		vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
	display_score(*vars);
	return (0);
}

/*
**	Function called when the cross of the window is clicked
**	Frees all the allocated memory and stop the program
*/

int	on_window_closed(t_vars *vars)
{
	free_and_close(vars);
	return (0);
}
