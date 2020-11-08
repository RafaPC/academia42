/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/08 12:12:13 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>
#include "../../printf/ft_printf.h"
#include <math.h>
#include <stdio.h>

int		on_key_pressed(int keycode, t_vars *vars)
{
	if (keycode == 'a')
		vars->keys_pressed.a = true;
	if (keycode == 'd')
		vars->keys_pressed.d = true;
	if (keycode == 'w')
		vars->keys_pressed.w = true;
	if (keycode == 's')
		vars->keys_pressed.s = true;
	//TODO: comprobar el escape
	return (0);
}

int		on_key_released(int keycode, t_vars *vars)
{
	if (keycode == 'a')
		vars->keys_pressed.a = false;
	if (keycode == 'd')
		vars->keys_pressed.d = false;
	if (keycode == 'w')
		vars->keys_pressed.w = false;
	if (keycode == 's')
		vars->keys_pressed.s = false;
	return (0);
}

void	check_movement(t_vars *vars)
{
	if (vars->keys_pressed.a)
	{
		vars->pangle += 0.1;
		if (vars->pangle > 2 * PI)
			vars->pangle -= 2 * PI;
		vars->pdx = cos(vars->pangle);
		vars->pdy = sin(vars->pangle);
	}
	if (vars->keys_pressed.d)
	{
		vars->pangle -= 0.1;
		if (vars->pangle < 0)
			vars->pangle += 2 * PI;
		vars->pdx = cos(vars->pangle);
		vars->pdy = sin(vars->pangle);
	}
	if (vars->keys_pressed.w)
	{	
		if (drawRays3D(vars, vars->pangle) > 0.5)
		{
			vars->px += vars->pdx * 0.1;
			vars->py -= vars->pdy * 0.1;
		}
	}
	if (vars->keys_pressed.s)
	{
		float opposite_angle = vars->pangle + PI - (vars->pangle > PI) ? 2 * PI : 0;
		float temp_angle = vars->pangle;
		vars->pangle = opposite_angle;
		float distance = drawRays3D(vars, opposite_angle);
		vars->pangle = temp_angle;
		if (distance > 0.2)
		{
			vars->px -= vars->pdx * 0.1;
			vars->py += vars->pdy * 0.1;
		}
	}
}

//TODO: funcion que se trigeree cuando se cambie de tamaño la ventana