/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/03 23:57:59 by rprieto-         ###   ########.fr       */
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
	float original_angle = vars->pangle;
	vars->pangle += PI/4;
	if (vars->pangle > 2 * PI)
		vars->pangle -= 2 * PI;
	for (int i = 0; i < 156; i++)
	{
		vars->pangle -= (PI/2)/156;
		if (vars->pangle < 0)
			vars->pangle += 2 * PI;
		render_column(vars, drawRays3D(vars));
	}
	vars->pangle = original_angle;
}

float	drawRays3D(t_vars *vars)
{
	//depending on the ray axis
	int tile_step_x, tile_step_y;
	float x_step, y_step;
	float x_intercept, y_intercept;
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
	//Esto podría agruparse en función de get_tangent
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
	//Set x_step and y_step
	y_step = (tile_step_y == 1) ? tang : -tang;
	x_step = (tile_step_x == 1) ? 1/tang : -1/tang;

	//Calculate x_intercept
	if (tile_step_y == 1)	//Facing downwards
		x_intercept = (ceil(vars->py) - vars->py) / tang;
	else
		x_intercept = (vars->py - floor(vars->py)) / tang;
	if (tile_step_x == 1)		//facing right
		x_intercept = vars->px + x_intercept;
	else						//facing left
		x_intercept = vars->px - x_intercept;
	//Calculate y_intercept
	if (tile_step_x == 1)
		y_intercept = (ceil(vars->px) - vars->px) * tang;
	else
		y_intercept = (vars->px - floor(vars->px)) * tang;
	if (tile_step_y == -1) //facing upwards
		y_intercept = vars->py - y_intercept;
	else
		y_intercept = vars->py + y_intercept;

	float x, y;
	x = floor(vars->px);
	y = floor(vars->py);
	printf("VARIABLES\nangulo: %f\ntangent: %f\ntile_step_x: %i tile_step_y: %i\n", vars->pangle * 180/PI ,tang, tile_step_x, tile_step_y);
	printf("COORDENADAS: X->%f  Y->%f\n", vars->px, vars->py);
	// printf("y_intercept: %f  y_step: %f\n", y_intercept, y_step);
	printf("x_intercept: %f  x_step: %f\n", x_intercept, x_step);
	printf("y_intercept: %f  y_step: %f\n", y_intercept, y_step);
	float distance = 999;
		printf("VERTICAL COLLISIONS\n");
		while (!completed && compare(y_intercept, (tile_step_y == 1) ? 8 : 0, (tile_step_y == 1) ? less_than : greater_than)
		&& ( x > 0 && x < 8))
		{
			x += tile_step_x;
			// printf("map[%i][%i] = %i\n", (int)floor(y_intercept), (int)x, map[(int)floor(y_intercept)][(int)x]);
			// printf("Corte: y_intercept: %f  x: %f\n", y_intercept, x);
			if (map[(int)floor(y_intercept)][(int)x] == 1)
			{
				// int color = create_trgb(0, 255, 0, 0);
				// draw_square(40, 40, x * 40, floor(y_intercept) * 40, color, vars);
				if (tile_step_x == 1)
					x = x - vars->px;
				else
					x = vars->px - x;
				if (tile_step_y == 1)
					y_intercept =  y_intercept - vars->py;
				else
					y_intercept = vars->py - y_intercept;
				distance = sqrt(y_intercept*y_intercept + x*x);
				printf("Distance: %f\n", distance);
				completed = true;
			}
			y_intercept += y_step;
		}
		completed = false;
		printf("---------------------\nHORIZONTAL COLLISIONS\n");
		while (!completed && compare(x_intercept, (tile_step_x == 1) ? 8 : 0, (tile_step_x == 1) ? less_than : greater_than)
		&& (y > 0 && y < 8))
		{
			y += tile_step_y;
			// printf("map[%i][%i] = %i\n", (int)y, (int)floor(x_intercept), map[(int)y][(int)floor(x_intercept)]);
			// printf("Corte: x_intercept: %f  y: %f\n", x_intercept, y);
			if (map[(int)y][(int)floor(x_intercept)] == 1)
			{
				// int color = create_trgb(0, 255, 0, 0);
				// draw_square(40, 40, floor(x_intercept) * 40, y * 40, color, vars);
				if (tile_step_x == 1)
					x_intercept = x_intercept - vars->px;
				else
					x_intercept = vars->px - x_intercept;
				if (tile_step_y == 1)
					y =  y - vars->py;
				else
					y = vars->py - y;
				float distance2 = sqrt(x_intercept*x_intercept + y*y);
				if (distance2 < distance)
				{
					distance = distance2;
					// printf("Distance nueva: %f\n", distance);
				}
				completed = true;
			}
			x_intercept += x_step;
		}
		if (!completed) //Comprobar rayo con paredes horizontales
			printf("WALL NOT FOUND\n");
	return (distance);
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

//EL PROBLEMA ES QUE IMPACTA EN DISTANCIA -1, DEBERÍA IMPACTAR EN MÁS Y QUEDARSE CON LA MENOR
//O SEA LA PRIMERA