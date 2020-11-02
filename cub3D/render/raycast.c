/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/02 18:20:23 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../cub3d.h"
#include <stdio.h>

void	drawRays3D(t_vars *vars)
{
	//depending on the ray axis
	int tile_step_x, tile_step_y;
	float x_step;
	float y_step;
	int x_intercept;
	int y_intercept;
	t_bool completed;
	int	map[8][8] =
	{
		{1,1,1,1,1,1,1,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	
	completed = false;
	set_tile_step(&tile_step_x, &tile_step_y, vars->pangle);
	x_step = tan(vars->pangle);
	y_step = 1/tan(vars->pangle);
	x_intercept = vars->px + (-(vars->py - floor(vars->py))/tan(vars->pangle));
	y_intercept = vars->py + ((vars->px - floor(vars->px))/tan(vars->pangle));
	
	int x, y;
	x = floor(vars->px);
	y = floor(vars->py);
	while (!completed)
	{
		while (!completed && compare(y_intercept, y, (tile_step_y == 1) ? greater_than : less_than))
		{
			if (map[x][y_intercept>>16] == 1)
			{
				printf("map[%i][%i]\n", x, y_intercept>>16);
				completed = true;
			}
			x += tile_step_x;
			y_intercept += y_step;
		}
	}
}

t_bool	compare(float n1, float n2, t_compare_flag compare_flag)
{
	if (compare_flag == greater_than)
		return (n1 > n2) ? true : false;
	else if (compare_flag == less_than)
		return (n1 < n2) ? true : false;
	return false;
}

void set_tile_step(int *tile_step_x, int *tile_step_y, float angle)
{
	if (angle >= 0 && angle <= PI)				//looking up
		*tile_step_y = -1;
	else										//looking down
		*tile_step_y = 1; 
	if (angle >= PI/2 && angle <= PI + PI/2)	//looking left
		*tile_step_x = -1;
	else										//looking right
		*tile_step_x = 1;
}