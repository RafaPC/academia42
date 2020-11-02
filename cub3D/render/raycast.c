/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/02 23:46:37 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "../cub3d.h"
#include "../../printf/ft_printf.h"

void	drawRays3D(t_vars *vars)
{
	//depending on the ray axis
	int tile_step_x, tile_step_y;
	float x_step;
	float y_step;
	float x_intercept;
	float y_intercept;
	float tang;
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
	tang = tan(vars->pangle);
	if (vars->pangle == 0 || vars->pangle == 180)
		tang = 0.1;
	else if (vars->pangle == 90 || vars->pangle == 270)
		tang = 10;

	completed = false;
	set_tile_step(&tile_step_x, &tile_step_y, vars->pangle);
	// x_step = (tile_step_x == 1) ? tang : -tang;
	// y_step = (tile_step_y == 1) ? 1/tang : -1/tang;
	y_step = (tile_step_y == 1) ? tang : -tang;
	//tangente negativa en cuadrante superior izquierdo e inferior derecho
	if (vars->pangle <= 2 * PI && vars->pangle >= PI + PI/2)
		y_step = -y_step;
	else if (vars->pangle >= 90 && vars->pangle <= 180)
		y_step = -y_step;
	x_step = (tile_step_x == 1) ? 1/tang : -1/tang;
	x_intercept = vars->px + (-(vars->py - floor(vars->py))/tang);
	y_intercept = vars->py + ((vars->px - floor(vars->px))/tang);
	float x, y;
	x = floor(vars->px);
	y = floor(vars->py);
	// printf("%f\n", vars->px - floor(vars->px));
	printf("VARIABLES\nangulo: %f\ntangent: %f\ntile_step_x: %i tile_step_y: %i\n", vars->pangle * 180/PI ,tang, tile_step_x, tile_step_y);
	printf("COORDENADAS: X->%f  Y->%f\n", vars->px, vars->py);
	printf("y_intercept: %f  y_step: %f\n", y_intercept, y_step);
	static int print = 0;
	while (!completed)
	{
		// ft_printf("primer while\n");
		// while (!completed && compare(y_intercept, y, (tile_step_y == 1) ? greater_than : less_than))
		while (!completed && ((int)floor(y_intercept) >= 0 && (int)floor(y_intercept) <= 8))
		{
			printf("map[%i][%i] = %i\n", (int)x, (int)floor(y_intercept), map[(int)x][(int)floor(y_intercept)]);
			// draw_square(40, 40, x * 40, floor(y_intercept) * 40, create_trgb(0, 0, 0, 200), vars);
			// if (map[(int)x][(int)floor(y_intercept)] == 1 || (int)floor(y_intercept) < 0 || (int)floor(y_intercept) > 8)
			if (map[(int)x][(int)floor(y_intercept)] == 1)
			{
				// draw_line(vars, x * 40, y_intercept * 40, create_trgb(0, 0, 200, 0));
				// printf("map[%i][%i]\n", (int)x, (int)floor(y_intercept));
				int color = create_trgb(0, 255, 0, 0);
				draw_square(40, 40, x * 40, floor(y_intercept) * 40, color, vars);
				print++;
				completed = true;
			}
			x += tile_step_x;
			y_intercept += y_step;
		}
		if (!completed)
			printf("WALL NOT FOUND\n");
		completed = true;
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