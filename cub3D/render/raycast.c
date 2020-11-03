/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/03 12:55:32 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "../cub3d.h"
#include "../../printf/ft_printf.h"

// void	drawRays3D(t_vars *vars)
// {
// 	//depending on the ray axis
// 	int tile_step_x, tile_step_y;
// 	float x_step;
// 	float y_step;
// 	float x_intercept;
// 	float y_intercept;
// 	float tang;
// 	t_bool completed;
// 	int	map[8][8] =
// 	{
// 		{1,1,1,1,1,1,1,1},
// 		{1,0,1,0,0,0,0,1},
// 		{1,0,1,0,0,0,0,1},
// 		{1,0,1,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,1,0,1},
// 		{1,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1}
// 	};
// 	tang = tan(vars->pangle);
// 	if (vars->pangle == 0 || vars->pangle == 180)
// 		tang = 0.1;
// 	else if (vars->pangle == 90 || vars->pangle == 270)
// 		tang = 10;

// 	completed = false;
// 	set_tile_step(&tile_step_x, &tile_step_y, vars->pangle);
// 	// x_step = (tile_step_x == 1) ? tang : -tang;
// 	// y_step = (tile_step_y == 1) ? 1/tang : -1/tang;
// 	y_step = (tile_step_y == 1) ? tang : -tang;
// 	//tangente negativa en cuadrante superior izquierdo e inferior derecho
// 	if (vars->pangle <= 2 * PI && vars->pangle >= (3*PI) / 2)
// 		y_step = -y_step;
// 	else if (vars->pangle >= PI/2 && vars->pangle <= PI)
// 		y_step = -y_step;
// 	x_step = (tile_step_x == 1) ? 1/tang : -1/tang;
// 	x_intercept = vars->px + (-(vars->py - floor(vars->py))/tang);
// 	// y_intercept = vars->py + ((vars->px - floor(vars->px))/tang);
// 	if (vars->pangle > PI/2 && vars->pangle < PI)
// 		y_intercept = (ceil(vars->px) - vars->px) * tang;
// 	else
// 		y_intercept = (ceil(vars->px) - vars->px) * -tang;
// 	float x, y;
// 	x = floor(vars->px);
// 	y = floor(vars->py);
// 	// printf("%f\n", vars->px - floor(vars->px));
// 	printf("VARIABLES\nangulo: %f\ntangent: %f\ntile_step_x: %i tile_step_y: %i\n", vars->pangle * 180/PI ,tang, tile_step_x, tile_step_y);
// 	printf("COORDENADAS: X->%f  Y->%f\n", vars->px, vars->py);
// 	printf("y_intercept: %f  y_step: %f\n", y_intercept, y_step);
// 	if (y_intercept < 0)
// 		y_intercept = -y_intercept;
// 	if (vars->pangle > PI && vars->pangle < 2*PI) //Mirando para abajo
// 		y_intercept += vars->py;
// 	else
// 		y_intercept = vars->py + y_intercept;
// 	printf("y_intercept: %f  y_step: %f\n", y_intercept, y_step);
// 	static int print = 0;
// 	while (!completed)
// 	{
// 		// ft_printf("primer while\n");
// 		while (!completed && compare(y_intercept, (tile_step_y == 1) ? 8 : 0, (tile_step_y == 1) ? less_than : greater_than)
// 		&& (x < 8 && x > 0))
// 		// while (!completed && ((int)floor(y_intercept) >= 0 && (int)floor(y_intercept) <= 8))
// 		{
// 			x += tile_step_x;
// 			printf("map[%i][%i] = %i\n", (int)floor(y_intercept), (int)x, map[(int)floor(y_intercept)][(int)x]);
			
// 			if (map[(int)floor(y_intercept)][(int)x] == 1)
// 			{
// 				int color = create_trgb(0, 255, 0, 0);
// 				draw_square(40, 40, x * 40, floor(y_intercept) * 40, color, vars);
// 				print++;
// 				completed = true;
// 			}
// 			// x += tile_step_x;
// 			y_intercept += y_step;
// 		}
// 		if (!completed)
// 			printf("WALL NOT FOUND\n");
// 		completed = true;
// 	}
// }

void	raycast(t_vars *vars)
{
	int start_angle = vars->pangle - (PI/4);
	int end_angle   = vars->pangle + (PI/4);
	if (start_angle < 0)
		start_angle += 2 * PI;
	if (end_angle > 2 * PI)
		end_angle -= 2 * PI;
	
	for ()
}

void	drawRays3D(t_vars *vars)
{
	//depending on the ray axis
	int tile_step_x, tile_step_y;
	float y_step;
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
	if (vars->pangle == 0 || vars->pangle == 180)
		tang = 0.1;
	else if (vars->pangle == 90 || vars->pangle == 270)
		tang = 10;
	else
		tang = tan(vars->pangle);
	if (tang < 0)
		tang = -tang;

	completed = false;
	set_tile_step(&tile_step_x, &tile_step_y, vars->pangle);
	y_step = (tile_step_y == 1) ? tang : -tang;
	y_intercept = (ceil(vars->px) - vars->px) * tang;
	if (tile_step_y == -1) //facing upwards
		y_intercept = vars->py - (tang * (ceil(vars->px) - vars->px));
	else
		y_intercept = vars->py + (tang * (ceil(vars->px) - vars->px));
	float x, y;
	x = floor(vars->px);
	y = floor(vars->py);
	printf("VARIABLES\nangulo: %f\ntangent: %f\ntile_step_x: %i tile_step_y: %i\n", vars->pangle * 180/PI ,tang, tile_step_x, tile_step_y);
	printf("COORDENADAS: X->%f  Y->%f\n", vars->px, vars->py);
	printf("y_intercept: %f  y_step: %f\n", y_intercept, y_step);
	while (!completed)
	{
		while (!completed && compare(y_intercept, (tile_step_y == 1) ? 8 : 0, (tile_step_y == 1) ? less_than : greater_than)
		&& (x < 8 && x > 0))
		{
			x += tile_step_x;
			printf("map[%i][%i] = %i\n", (int)floor(y_intercept), (int)x, map[(int)floor(y_intercept)][(int)x]);
			
			if (map[(int)floor(y_intercept)][(int)x] == 1)
			{
				int color = create_trgb(0, 255, 0, 0);
				draw_square(40, 40, x * 40, floor(y_intercept) * 40, color, vars);
				completed = true;
			}
			y_intercept += y_step;
		}
		if (!completed) //Comprobar rayo con paredes horizontales
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