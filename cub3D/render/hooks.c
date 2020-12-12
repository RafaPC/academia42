/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/11 13:48:28 by rprieto-         ###   ########.fr       */
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
	//TODO: comprobar el escape
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

void	check_collision(t_vars *vars)
{
	float	newX;
	float	newY;

	newX = vars->player_vars.px + vars->player_vars.pdx * 0.3;
	newY = vars->player_vars.py - vars->player_vars.pdy * 0.3;
	printf("Position x: %f  y: %f\n", vars->player_vars.px, vars->player_vars.py);
	printf("map[%i][%i]=%c\n", (int)newY, (int)newX, vars->map[(int)newY][(int)newX]);
	if (vars->map[(int)newY][(int)newX] == '1')
	{
		if (vars->map[(int)newY][(int)vars->player_vars.px] != '1')
			vars->player_vars.py -= vars->player_vars.pdy * 0.1;
		else if (vars->map[(int)vars->player_vars.py][(int)newX] != '1')
			vars->player_vars.px += vars->player_vars.pdx * 0.1;
	}
	else
	{
		vars->player_vars.py -= vars->player_vars.pdy * 0.1;
		vars->player_vars.px += vars->player_vars.pdx * 0.1;
	}
	// if (vars->keys_pressed.w)
	// {	
	// 	if (88888 > 0.5)
	// 	{
	// 		vars->player_vars.px += vars->player_vars.pdx * 0.1;
	// 		vars->player_vars.py -= vars->player_vars.pdy * 0.1;
	// 	}
	// }
}

//TODO: Checkear las colisiones
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
	if (vars->keys_pressed.a)
		move_left(vars);
	if (vars->keys_pressed.d)
		move_right(vars);
	if (vars->keys_pressed.w || vars->keys_pressed.s)
		check_collision(vars);
}

void	move_left(t_vars *vars)
{
	float new_angle = vars->player_vars.pangle + PI/2;
	if (new_angle > 2*PI)
		new_angle -= 2*PI;
	vars->player_vars.px += cosf(new_angle) * 0.05;
	vars->player_vars.py -= sinf(new_angle) * 0.05;
}

void	move_right(t_vars *vars)
{
	float new_angle = vars->player_vars.pangle - PI/2;
	if (new_angle < 0)
		new_angle += 2*PI;
	vars->player_vars.px += cosf(new_angle) * 0.05;
	vars->player_vars.py -= sinf(new_angle) * 0.05;
}

//TODO: funcion que se trigeree cuando se cambie de tamaño la ventana