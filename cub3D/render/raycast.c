/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/05 18:31:31 by rprieto-         ###   ########.fr       */
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
	float angle;
	float screen_width = 1600;
	float sixty_dg = 1.0472;
	float ninety_dg = 1.57079;
	for (float col = 0; col < screen_width; col++)
	{
		angle = vars->pangle - atan(tan(sixty_dg / 2.0) * (2.0 * col / screen_width - 1.0));
		check_angle_overflow(&angle);
		render_column(vars, drawRays3D_test(vars, angle));
	}
}

float	drawRays3D_debug(t_vars *vars, float angle)
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
	completed = false;
	tang = get_tangent(angle);
	set_tile_step(&tile_step_x, &tile_step_y, angle);
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
	printf("VARIABLES\nangulo: %f\ntangent: %f\ntile_step_x: %i tile_step_y: %i\n", angle * 180/PI, tang, tile_step_x, tile_step_y);
	printf("COORDENADAS: X->%f  Y->%f\n", vars->px, vars->py);
	printf("x_intercept: %f  x_step: %f\n", x_intercept, x_step);
	printf("y_intercept: %f  y_step: %f\n", y_intercept, y_step);
	float distance = 999;
	printf("VERTICAL COLLISIONS\n");
	while (!completed && compare(y_intercept, (tile_step_y == 1) ? 8 : 0, (tile_step_y == 1) ? less_than : greater_than)
	&& ( x > 0 && x < 8))
	{
		x += tile_step_x;
		printf("map[%i][%i] = %i\n", (int)floor(y_intercept), (int)x, map[(int)floor(y_intercept)][(int)x]);
		printf("Corte: y_intercept: %f  x: %f\n", y_intercept, x);
		if (map[(int)floor(y_intercept)][(int)x] == 1)
		{
			// int color = create_trgb(0, 255, 0, 0);
			// draw_square(40, 40, x * 40, floor(y_intercept) * 40, color, vars);
			if (tile_step_x == 1)
				x = x - vars->px;
			else
				x = vars->px - x - 1; //Importante el -1
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
	if (completed)
		printf("Vertical collision at map[%i][%i]\n", (int)floor(y_intercept), (int)x);
	else
		printf("NO vertical collision");
	completed = false;
	printf("---------------------\nHORIZONTAL COLLISIONS\n");
	while (!completed && compare(x_intercept, (tile_step_x == 1) ? 8 : 0, (tile_step_x == 1) ? less_than : greater_than)
	&& (y > 0 && y < 8))
	{
		y += tile_step_y;
		printf("map[%i][%i] = %i\n", (int)y, (int)floor(x_intercept), map[(int)y][(int)floor(x_intercept)]);
		printf("Corte: x_intercept: %f  y: %f\n", x_intercept, y);
		float old_x_intercept = x_intercept;
		float old_y = y;
		if (map[(int)y][(int)floor(x_intercept)] == 1)
		{
			if (tile_step_x == 1)
				x_intercept = x_intercept - vars->px;
			else
				x_intercept = vars->px - x_intercept;
			if (tile_step_y == 1)
				y =  y - vars->py;
			else
				y = vars->py - y - 1; //Importante el -1
			float distance2 = sqrt(x_intercept*x_intercept + y*y);
			if (distance2 < distance)
			{
				// int color = create_trgb(0, 0, 255, 0);
				// if	(tile_step_x == -1)
				// 	old_x_intercept -= 1;
				// draw_square(40, 40, floor(old_x_intercept) * 40, old_y * 40, color, vars);
				distance = distance2;
				printf("Distance nueva: %f\n", distance);
			}
			completed = true;
		}
		if (completed)
			printf("Horizontal collision at map[%i][%i]\n", (int)old_y, (int)floor(old_x_intercept));
		else
			printf("NO horizontal collision");
		x_intercept += x_step;
	}
	float angle_beta = angle - vars->pangle;
	if (angle_beta < 0)
		angle_beta += 2 * PI;
	if (angle_beta > 2 * PI)
		angle_beta -= 2 * PI;
	printf("ANGLE INFO:\n");
	printf("Player angle: %fº - Ray angle: %fº\n", vars->pangle * 180/PI, angle * 180/PI);
	printf("Angle difference: %fº\n", angle_beta * 180/PI);
	distance = distance * cos(angle_beta);
	printf("Distancia sin fisheye: %f\n", distance);
	return (distance);
}

float	drawRays3D(t_vars *vars, float angle)
{
	//depending on the ray axis
	t_ray ray;
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
	tang = get_tangent(angle);
	completed = false;
	set_tile_step(&ray.tile_step_x, &ray.tile_step_y, angle);
	//Set x_step and y_step
	ray.y_step = (ray.tile_step_y == 1) ? tang : -tang;
	ray.x_step = (ray.tile_step_x == 1) ? 1/tang : -1/tang;

	//Calculate x_intercept
	if (ray.tile_step_y == 1)	//Facing downwards
		ray.x_intercept = (ceilf(vars->py) - vars->py) / tang;
	else
		ray.x_intercept = (vars->py - floorf(vars->py)) / tang;
	if (ray.tile_step_x == 1)		//facing right
		ray.x_intercept = vars->px + ray.x_intercept;
	else						//facing left
		ray.x_intercept = vars->px - ray.x_intercept;
	//Calculate y_intercept
	if (ray.tile_step_x == 1)
		ray.y_intercept = (ceilf(vars->px) - vars->px) * tang;
	else
		ray.y_intercept = (vars->px - floorf(vars->px)) * tang;
	if (ray.tile_step_y == -1) //facing upwards
		ray.y_intercept = vars->py - ray.y_intercept;
	else
		ray.y_intercept = vars->py + ray.y_intercept;

	float x, y;
	x = floorf(vars->px);
	y = floorf(vars->py);
	float distance = 999;
	while (!completed && compare(ray.y_intercept, (ray.tile_step_y == 1) ? 8 : 0,
	(ray.tile_step_y == 1) ? less_than : greater_than) && (x > 0 && x < 8))
	{
		x += ray.tile_step_x;
		if (map[(int)floorf(ray.y_intercept)][(int)x] == 1)
		{
			if (ray.tile_step_x == 1)
				x = x - vars->px;
			else
				x = vars->px - x - 1; //Importante el -1
			if (ray.tile_step_y == 1)
				ray.y_intercept =  ray.y_intercept - vars->py;
			else
				ray.y_intercept = vars->py - ray.y_intercept;
			distance = sqrtf(ray.y_intercept*ray.y_intercept + x*x);
			completed = true;
			vars->wall_face = 1;
		}
		ray.y_intercept += ray.y_step;
	}
	completed = false;
	while (!completed && compare(ray.x_intercept, (ray.tile_step_x == 1) ? 8 : 0, (ray.tile_step_x == 1) ? less_than : greater_than)
	&& (y > 0 && y < 8))
	{
		y += ray.tile_step_y;
		if (map[(int)y][(int)floorf(ray.x_intercept)] == 1)
		{
			if (ray.tile_step_x == 1)
				ray.x_intercept = ray.x_intercept - vars->px;
			else
				ray.x_intercept = vars->px - ray.x_intercept;
			if (ray.tile_step_y == 1)
				y =  y - vars->py;
			else
				y = vars->py - y - 1; //Importante el -1
			float distance2 = sqrtf(ray.x_intercept*ray.x_intercept + y*y);
			if (distance2 < distance)
			{
				distance = distance2;
				vars->wall_face = 2;
			}
			completed = true;
		}
		ray.x_intercept += ray.x_step;
	}
	float angle_beta = angle - vars->pangle;
	check_angle_overflow(&angle_beta);
	distance *= cosf(angle_beta);
	return (distance);
}

float	drawRays3D_test(t_vars *vars, float angle)
{
	//depending on the ray axis
	t_ray ray;
	float tang;
	float distance_hor;
	float distance_ver;
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
	tang = get_tangent(angle);
	completed = false;
	//Fix fisheye effect
	float angle_beta = angle - vars->pangle;
	check_angle_overflow(&angle_beta);

	//Setting tile_setps accordingly to the quadrant
	set_tile_step(&ray.tile_step_x, &ray.tile_step_y, angle);
	
	//Set x_step and y_step
	ray.y_step = (ray.tile_step_y == 1) ? tang : -tang;
	ray.x_step = (ray.tile_step_x == 1) ? 1/tang : -1/tang;

	//Calculate x_intercept
	if (ray.tile_step_y == 1)		//Facing downwards
		ray.x_intercept = (ceilf(vars->py) - vars->py) / tang;
	else
		ray.x_intercept = (vars->py - floorf(vars->py)) / tang;
	if (ray.tile_step_x == 1)		//facing right
		ray.x_intercept = vars->px + ray.x_intercept;
	else							//facing left
		ray.x_intercept = vars->px - ray.x_intercept;
	//Calculate y_intercept
	if (ray.tile_step_x == 1)
		ray.y_intercept = (ceilf(vars->px) - vars->px) * tang;
	else
		ray.y_intercept = (vars->px - floorf(vars->px)) * tang;
	if (ray.tile_step_y == -1) 		//facing upwards
		ray.y_intercept = vars->py - ray.y_intercept;
	else
		ray.y_intercept = vars->py + ray.y_intercept;

	ray.x = floorf(vars->px);
	ray.y = floorf(vars->py);
	ray.x += ray.tile_step_x;
	ray.y += ray.tile_step_y;
	while (!completed)
	{
		distance_hor = get_x_intercept_length(ray, *vars);
		distance_ver = get_y_intercept_length(ray, *vars);
		if (distance_hor < distance_ver)
		{
			ray.x_intercept += ray.x_step;
			ray.y += ray.tile_step_y;
		}
		else
		{
			ray.y_intercept += ray.y_step;
			ray.x += ray.tile_step_x;
		}
		if (map[(int)floorf(ray.y_intercept)][(int)ray.x] == 1 ||
		map[(int)ray.y][(int)floorf(ray.x_intercept)] == 1)
		{
			if (distance_hor < distance_ver)
				return (distance_hor * cosf(angle_beta));
			else
				return (distance_ver * cosf(angle_beta));
			completed = true;
		}
	}	
	return (1);
}

t_bool	compare(float n1, float n2, t_compare_flag compare_flag)
{
	if (compare_flag == greater_than)
		return (n1 > n2) ? true : false;
	else if (compare_flag == less_than)
		return (n1 < n2) ? true : false;
	return false;
}

void	set_tile_step(int *tile_step_x, int *tile_step_y, float angle)
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

float	get_x_intercept_length(t_ray ray, t_vars vars)
{
	float distance;
	float x;
	float y;

	if (ray.tile_step_x == 1)
		x = ray.x_intercept - vars.px;
	else
		x = vars.px - ray.x_intercept;
	if (ray.tile_step_y == 1)
		y =  ray.y - vars.py;
	else
		y = vars.py - ray.y - 1; //Importante el -1
	distance = sqrtf(x * x + y * y);
	return (distance);
}

float	get_y_intercept_length(t_ray ray, t_vars vars)
{
	float distance;
	float x;
	float y;

	if (ray.tile_step_x == 1)
		x = ray.x - vars.px;
	else
		x = vars.px - ray.x - 1; //Importante el -1
	if (ray.tile_step_y == 1)
		y =  ray.y_intercept - vars.py;
	else
		y = vars.py - ray.y_intercept;
	distance = sqrtf(x * x + y * y);
	return (distance);
}

/*
**		Receives an angle and returns its tangent avoiding limits and negative values
*/
float	get_tangent(float angle)
{
	float tangent;

	if (angle == 0 || angle == 180)
		tangent = 0.1;
	else if (angle == 90 || angle == 270)
		tangent = 10;
	else
		tangent = tanf(angle);
	tangent = fabsf(tangent);
	return (tangent);
}

/*
**	Check if the given angle is under 0 or over 2PI and corrects it
*/
void check_angle_overflow(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

//CHECKEAR ESTO
 //perform DDA
/* while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
    }
*/