/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/14 16:22:31 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>
#include <stdio.h>

int		on_key_pressed(int keycode, t_keys *keys_pressed)
{
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

void	move(t_vars*vars, float angle, float velocity)
{	 
	float	newX;
	float	newY;
	float	pdx;
	float	pdy;

	check_angle_overflow(&angle);
	pdx = cosf(angle);
	pdy = sinf(angle);
	newX = vars->player_vars.px + pdx * (0.3 * velocity);
	newY = vars->player_vars.py - pdy * (0.3 * velocity);
	if (vars->map[(int)newY][(int)vars->player_vars.px] == '1')
	{
		if (vars->map[(int)vars->player_vars.py][(int)newX] != '1')
			vars->player_vars.px += pdx * (0.05 * velocity);
	}
	else
		vars->player_vars.py -= pdy * (0.1 * velocity);
	
	if (vars->map[(int)vars->player_vars.py][(int)newX] == '1')
	{
		if (vars->map[(int)newY][(int)vars->player_vars.px] != '1')
			vars->player_vars.py -= pdy * (0.05 * velocity);
	}
	else
		vars->player_vars.px += pdx * (0.1 * velocity);
}

void	check_movement(t_vars *vars)
{
	if (vars->keys_pressed.left_arrow)
	{
		vars->player_vars.pangle += 0.1;
		if (vars->player_vars.pangle > 2 * PI)
			vars->player_vars.pangle -= 2 * PI;
		vars->player_vars.pdx = cosf(vars->player_vars.pangle);
		vars->player_vars.pdy = sinf(vars->player_vars.pangle);
	}
	if (vars->keys_pressed.right_arrow)
	{
		vars->player_vars.pangle -= 0.1;
		if (vars->player_vars.pangle < 0)
			vars->player_vars.pangle += 2 * PI;
		vars->player_vars.pdx = cosf(vars->player_vars.pangle);
		vars->player_vars.pdy = sinf(vars->player_vars.pangle);
	}
	if (vars->keys_pressed.w)
		move(vars, vars->player_vars.pangle, 1);
	if (vars->keys_pressed.a)
		move(vars, vars->player_vars.pangle + PI/2, 0.3);
	if (vars->keys_pressed.s)
		move(vars, vars->player_vars.pangle - PI, 0.5);
	if (vars->keys_pressed.d)
		move(vars, vars->player_vars.pangle - PI/2, 0.3);
}

/*
** //TODO: funcion que se trigeree cuando se vuelva a entrar a la ventana
*/

int		on_window_enter(t_vars *vars)
{
	// printf("entra\n");
	return (0);
}

int		on_window_closed(t_vars *vars)
{

	return (0);
}

void	close_game(t_vars *vars)
{
	
}