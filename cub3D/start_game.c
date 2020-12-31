/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/31 17:36:18 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "mlx.h"
#include "cub3d.h"

/*
**		TODO:
*/

void	start_game(t_program_params params, t_bool screenshot)
{
	t_vars			vars;
	t_bool			initialiced;

	initialiced = init_game_variables(&vars, params);
	free_program_params(params);
	if (!initialiced)
		free_and_close(&vars);
	if (screenshot)
		take_screenshot(vars);
	else
	{
		if (!(vars.mlx.win = mlx_new_window(vars.mlx.mlx, vars.window_width,
		vars.window_height, "Cub3D")))
			free_and_close(&vars);
		mlx_put_image_to_window(vars.mlx.mlx, vars.mlx.win,
			vars.mlx.img->img, 0, 0);
		raycast(&vars);
		render_sprites(&vars);
		mlx_put_image_to_window(
			vars.mlx.mlx, vars.mlx.win, vars.mlx.img->img, 0, 0);
		set_hooks(&vars);
		mlx_loop(vars.mlx.mlx);
	}
}

/*
**		Set hooks for the input
*/

void	set_hooks(t_vars *vars)
{
	mlx_hook(vars->mlx.win, KeyPress, KeyPressMask, on_key_pressed, vars);
	mlx_hook(vars->mlx.win, KeyRelease, KeyReleaseMask,
		on_key_released, &vars->keys_pressed);
	mlx_hook(vars->mlx.win, FocusIn, FocusChangeMask, on_window_focused, vars);
	mlx_hook(vars->mlx.win, ClientMessage, NoEventMask,
		on_window_closed, vars);
	mlx_loop_hook(vars->mlx.mlx, render_screen, vars);
}
