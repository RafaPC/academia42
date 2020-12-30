/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/30 12:26:55 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "cub3d.h"

/*
**		Iterates as many times as window width getting the proper
**		distance and x_wall values for each column to render them right
*/

void	raycast(t_vars *vars)
{
	float	angle;
	float	x_wall;
	int		x_coord;

	x_coord = 0;
	while (x_coord < vars->window_width)
	{
		angle = vars->player.angle - atanf(tanf(FOV / 2.0) *
		(2.0 * x_coord / vars->window_width - 1.0));
		check_angle_overflow(&angle);
		vars->distances[x_coord] =
			get_distance_to_wall(vars, angle, x_coord, &x_wall);
		render_column(vars, vars->distances[x_coord], x_wall, x_coord);
		x_coord++;
	}
}

/*
**		Iterates checking wether the ray meets a wall advancing the collision
**		coordinates with vertical and horizontal walls
**		It never reach an infinite loop because the map is checked to be
**		surrounded by walls
*/

float	get_distance_to_wall(t_vars *vars, float angle, int x_coord,
float *x_wall)
{
	t_ray	ray;

	init_ray_values(&ray, vars->player, angle);
	while (true)
	{
		ray.direction = (ray.distance_hor < ray.distance_ver) ? 1 : 0;
		set_tile_crossed(&ray, vars->map);
		check_sprite_crossed(ray, ray.tile_crossed, vars);
		if (ray.tile_crossed == '1' && ray.direction == horizontal)
		{
			vars->distances[x_coord] = ray.distance_hor;
			vars->wall_face = (ray.tile_step_y == 1) ? north_face : south_face;
			*x_wall = ray.x_intercept - ray.x;
			return (ray.distance_hor * cosf(ray.angle_beta));
		}
		else if (ray.tile_crossed == '1' && ray.direction == vertical)
		{
			vars->distances[x_coord] = ray.distance_ver;
			vars->wall_face = (ray.tile_step_x == 1) ? west_face : east_face;
			*x_wall = ray.y_intercept - ray.y;
			return (ray.distance_ver * cosf(ray.angle_beta));
		}
		sum_distance(&ray, vars->player);
	}
	return (1.0);
}

/*
**	Advances the shortest distance to the next intersection
*/

void	sum_distance(t_ray *ray, t_player_vars player)
{
	if (ray->distance_hor < ray->distance_ver)
	{
		ray->x_intercept += ray->x_step;
		ray->y += ray->tile_step_y;
		ray->distance_hor = get_x_intercept_length(*ray, player);
	}
	else
	{
		ray->y_intercept += ray->y_step;
		ray->x += ray->tile_step_x;
		ray->distance_ver = get_y_intercept_length(*ray, player);
	}
}

/*
**		Initialices ray values such as ray coordinates, first intersections
**		with horizontal and vertical walls, steps in each axis to reach
**		the next intersections, distances to each intersection type
**		(vertical and horizontal)
*/

void	init_ray_values(t_ray *ray, t_player_vars player, float angle)
{
	init_ray_values2(ray, angle);
	ray->y_step = (ray->tile_step_y == 1) ? ray->tang : -ray->tang;
	ray->x_step = (ray->tile_step_x == 1) ? 1 / ray->tang : -1 / ray->tang;
	if (ray->tile_step_y == 1)
		ray->x_intercept = (floorf(player.y + 1) - player.y) / ray->tang;
	else
		ray->x_intercept = (player.y - floorf(player.y)) / ray->tang;
	if (ray->tile_step_x == 1)
		ray->x_intercept = player.x + ray->x_intercept;
	else
		ray->x_intercept = player.x - ray->x_intercept;
	if (ray->tile_step_x == 1)
		ray->y_intercept = (floorf(player.x + 1) - player.x) * ray->tang;
	else
		ray->y_intercept = (player.x - floorf(player.x)) * ray->tang;
	ray->y_intercept = (ray->tile_step_y == 1)
	? player.y + ray->y_intercept : player.y - ray->y_intercept;
	ray->angle_beta = angle - player.angle;
	check_angle_overflow(&ray->angle_beta);
	ray->x = floorf(player.x);
	ray->y = floorf(player.y);
	ray->distance_hor = get_x_intercept_length(*ray, player);
	ray->distance_ver = get_y_intercept_length(*ray, player);
}

/*
**		Inicialices tile steps in both axis and
**		the tangent avoiding negative values and limits
*/

void	init_ray_values2(t_ray *ray, float angle)
{
	if (angle >= 0 && angle <= PI)
		ray->tile_step_y = -1;
	else
		ray->tile_step_y = 1;
	if (angle >= PI / 2 && angle <= PI + PI / 2)
		ray->tile_step_x = -1;
	else
		ray->tile_step_x = 1;
	if (angle == 0 || angle == 180)
		ray->tang = 0.1;
	else if (angle == 90 || angle == 270)
		ray->tang = 10;
	else
		ray->tang = fabsf(tanf(angle));
}
