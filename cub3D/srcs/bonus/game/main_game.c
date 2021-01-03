/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 21:02:33 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_printf.h"

/*
**		Calls functions to initialice the variables needed and then
**		renders and saves an image in .bmp format or starts the game
**		If something goes wrong while initialicing variables frees everything
**		and closes the program
*/

void	start_game(t_program_params params, t_bool screenshot)
{
	t_vars			vars;
	t_bool			initialiced;

	init_to_null(&vars);
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
	mlx_hook(vars->mlx.win, KeyRelease, KeyReleaseMask, on_key_released, vars);
	mlx_hook(vars->mlx.win, FocusIn, FocusChangeMask, on_window_focused, vars);
	mlx_hook(vars->mlx.win, ClientMessage, NoEventMask,
		on_window_closed, vars);
	mlx_loop_hook(vars->mlx.mlx, render_screen, vars);
}

/*
**		Shrinks the window size if the parameters are bigger than the screen
*/

void	set_window_size(t_vars *vars, int window_width, int window_height)
{
	int screen_width;
	int screen_height;

	mlx_get_screen_size(vars->mlx.mlx, &screen_width, &screen_height);
	if (screen_width < window_width)
	{
		vars->window_width = screen_width;
		ft_printf("Window width will be shrinked to screen width\n");
	}
	else
		vars->window_width = window_width;
	if (screen_height < window_height)
	{
		vars->window_height = screen_height;
		ft_printf("Window height will be shrinked to screen height\n");
	}
	else
		vars->window_height = window_height;
}
