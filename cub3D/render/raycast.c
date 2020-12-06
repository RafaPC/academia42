/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/03 19:46:48 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "cub3d.h"

int debug = 1;
int offset_column2 = 0;

void	raycast(t_vars *vars)
{
	debug = 0;
	float angle;
	int screen_width = 800;
	float distance;
	for (int col = 0; col < screen_width; col++)
	{
		angle = vars->pangle - atanf(tanf(FOV / 2.0) * (2.0 * col / screen_width - 1.0));
		check_angle_overflow(&angle);
		distance = drawRays3D(vars, angle);
		vars->distances[offset_column2] = distance;
		render_column(vars, distance);
		debug = 0;
	}
	offset_column2 = 0;
}

float	drawRays3D(t_vars *vars, float angle)
{
	//depending on the ray axis
	t_ray ray;
	float distance_hor;
	float distance_ver;
	int	map[8][8] =
	{
		{1,1,1,1,1,1,1,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,2,0,1},
		{1,0,1,0,0,2,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,2,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	//Fix fisheye effect
	float angle_beta = angle - vars->pangle;
	check_angle_overflow(&angle_beta);
	//Initialice values
	ray = init_ray_values(*vars, angle);
	distance_hor = get_x_intercept_length(ray, *vars);
	distance_ver = get_y_intercept_length(ray, *vars);
	//TODO: Maybe calcular simplemente la distancia perpendicular y cuando compruebe que choca
	//con una pared entonces calcular la relativa a donde mira el jugador

	int tile_crossed = 0;
	int ray_direction = 0; //0 vertical 1 horizontal
	while (true)
	{
		ray_direction = (distance_hor < distance_ver) ? 0 : 1;
		//Solo comprobar si el menor choca con pared
		if (distance_hor < distance_ver)
			tile_crossed = map[(int)ray.y + ray.tile_step_y][(int)floorf(ray.x_intercept)];
		else
			tile_crossed = map[(int)floorf(ray.y_intercept)][(int)ray.x + ray.tile_step_x];
		
		if (tile_crossed == 2 && ray_direction == 0)
			add_sprite_coords((int)floorf(ray.x_intercept), (int)ray.y + ray.tile_step_y, vars);
		else if (tile_crossed == 2 && ray_direction == 1)
			add_sprite_coords((int)ray.x + ray.tile_step_x, (int)floorf(ray.y_intercept), vars);
		
		if (tile_crossed == 1 && ray_direction == 0)
		{
			//Guardar la distancia
			vars->distances[offset_column2++] = distance_hor;
			vars->wall_face = (ray.tile_step_y == 1) ? north_face : south_face;
			vars->texture_x = ray.x_intercept - ray.x;
			return (distance_hor * cosf(angle_beta));
		}
		else if (tile_crossed == 1 && ray_direction == 1)
		{
			//Guardar la distancia
			vars->distances[offset_column2++] = distance_ver;
			vars->wall_face = (ray.tile_step_x == 1) ? west_face : east_face;
			vars->texture_x = ray.y_intercept - ray.y;
			return (distance_ver * cosf(angle_beta));
		}
		
		if (distance_hor < distance_ver)
		{
			ray.x_intercept += ray.x_step;
			ray.y += ray.tile_step_y;
			distance_hor = get_x_intercept_length(ray, *vars);
		}
		else
		{
			ray.y_intercept += ray.y_step;
			ray.x += ray.tile_step_x;
			distance_ver = get_y_intercept_length(ray, *vars);
		}
	}
	return (1);
}

t_ray	init_ray_values(t_vars vars, float angle)
{
	t_ray ray;

	ray.tang = get_tangent(angle);
	//Setting tile_setps accordingly to the quadrant
	set_tile_step(&ray.tile_step_x, &ray.tile_step_y, angle);
	//Set x_step and y_step
	ray.y_step = (ray.tile_step_y == 1) ? ray.tang : -ray.tang;
	ray.x_step = (ray.tile_step_x == 1) ? 1/ray.tang : -1/ray.tang;

	//Calculate x_intercept
	if (ray.tile_step_y == 1)		//Facing downwards
		ray.x_intercept = (ceilf(vars.py) - vars.py) / ray.tang;
	else
		ray.x_intercept = (vars.py - floorf(vars.py)) / ray.tang;
	if (ray.tile_step_x == 1)		//facing right
		ray.x_intercept = vars.px + ray.x_intercept;
	else							//facing left
		ray.x_intercept = vars.px - ray.x_intercept;
	//Calculate y_intercept
	if (ray.tile_step_x == 1)
		ray.y_intercept = (ceilf(vars.px) - vars.px) * ray.tang;
	else
		ray.y_intercept = (vars.px - floorf(vars.px)) * ray.tang;
	if (ray.tile_step_y == -1) 		//facing upwards
		ray.y_intercept = vars.py - ray.y_intercept;
	else
		ray.y_intercept = vars.py + ray.y_intercept;

	ray.x = floorf(vars.px);
	ray.y = floorf(vars.py);
	return (ray);
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

//FIXME: Calcular esto sin el cuadrado, con senos y cosenos
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
		y =  (ray.y + 1) - vars.py;
	else
		y = vars.py - ray.y;	
	// y = vars.py - ray.y - 1; //Importante el -1
	distance = sqrtf(x * x + y * y);
	return (distance);
}

//FIXME: Calcular esto sin el cuadrado, con senos y cosenos
float	get_y_intercept_length(t_ray ray, t_vars vars)
{
	float distance;
	float x;
	float y;

	if (ray.tile_step_x == 1)
		x = (ray.x + 1) - vars.px;
		// x = ray.x - vars.px;
	else
		x = vars.px - ray.x;
		// x = vars.px - ray.x - 1; //Importante el -1
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
