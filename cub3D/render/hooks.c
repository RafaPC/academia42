/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/02 23:56:56 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>
#include "../../printf/ft_printf.h"
#include <math.h>
#include <stdio.h>

int		on_key_pressed(int keycode,t_vars *vars)
{
	ft_printf("key %i\n", keycode);
	if (keycode == 'a')
	{
		vars->pangle += 0.2;
		if (vars->pangle > 2 * PI)
			vars->pangle -= 2 * PI;
		vars->pdx = cos(vars->pangle);
		vars->pdy = sin(vars->pangle);
	}
	if (keycode == 'd')
	{
		vars->pangle -= 0.2;
		if (vars->pangle < 0)
			vars->pangle += 2 * PI;
		vars->pdx = cos(vars->pangle);
		vars->pdy = sin(vars->pangle);
	}
	if (keycode == 'w')
	{
		vars->px += vars->pdx * 0.2;
		vars->py -= vars->pdy * 0.2;
	}
	if (keycode == 's')
	{
		vars->px -= vars->pdx * 0.2;
		vars->py += vars->pdy * 0.2;
	}
	render_screen(vars);
	return (0);
}
