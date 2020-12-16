/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/16 12:20:34 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "cub3d.h"

void	raycast(t_vars *vars)
{
	float	angle;
	float	x_wall;
	int		x_coord;

	x_coord = 0;
	while (x_coord < vars->screen_width)
	{
		angle = vars->player.angle - atanf(tanf(FOV / 2.0) *
		(2.0 * x_coord / vars->screen_width - 1.0));
		check_angle_overflow(&angle);
		vars->distances[x_coord] =
		get_distance_to_wall(vars, angle, x_coord, &x_wall);
		render_column(vars, vars->distances[x_coord], x_wall, x_coord);
		x_coord++;
	}
}

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
	return (1);
}

void	check_sprite_crossed(t_ray ray, char tile_crossed, t_vars *vars)
{
	if (tile_crossed == '2')
	{
		if (ray.direction == horizontal)
			add_sprite_coords((int)floorf(ray.x_intercept),
			(int)ray.y + ray.tile_step_y, vars);
		else if (ray.direction == vertical)
			add_sprite_coords((int)ray.x + ray.tile_step_x,
			(int)floorf(ray.y_intercept), vars);
	}
}

void	set_tile_crossed(t_ray *ray, char **map)
{
	if (ray->distance_hor < ray->distance_ver)
		ray->tile_crossed = map[(int)ray->y + ray->tile_step_y]
		[(int)floorf(ray->x_intercept)];
	else
		ray->tile_crossed = map[(int)floorf(ray->y_intercept)]
		[(int)ray->x + ray->tile_step_x];
}

/*
**	Suma la distancia más corta u know
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

void	init_ray_values(t_ray *ray, t_player_vars player, float angle)
{
	ray->tang = get_tangent(angle);
	set_tile_step(&ray->tile_step_x, &ray->tile_step_y, angle);
	ray->y_step = (ray->tile_step_y == 1) ? ray->tang : -ray->tang;
	ray->x_step = (ray->tile_step_x == 1) ? 1 / ray->tang : -1 / ray->tang;
	if (ray->tile_step_y == 1)
		ray->x_intercept = (ceilf(player.y) - player.y) / ray->tang;
	else
		ray->x_intercept = (player.y - floorf(player.y)) / ray->tang;
	if (ray->tile_step_x == 1)
		ray->x_intercept = player.x + ray->x_intercept;
	else
		ray->x_intercept = player.x - ray->x_intercept;
	if (ray->tile_step_x == 1)
		ray->y_intercept = (ceilf(player.x) - player.x) * ray->tang;
	else
		ray->y_intercept = (player.x - floorf(player.x)) * ray->tang;
	if (ray->tile_step_y == -1)
		ray->y_intercept = player.y - ray->y_intercept;
	else
		ray->y_intercept = player.y + ray->y_intercept;
	ray->angle_beta = angle - player.angle;
	check_angle_overflow(&ray->angle_beta);
	ray->x = floorf(player.x);
	ray->y = floorf(player.y);
	ray->distance_hor = get_x_intercept_length(*ray, player);
	ray->distance_ver = get_y_intercept_length(*ray, player);
}

void	set_tile_step(int *tile_step_x, int *tile_step_y, float angle)
{
	if (angle >= 0 && angle <= PI)
		*tile_step_y = -1;
	else
		*tile_step_y = 1;
	if (angle >= PI / 2 && angle <= PI + PI / 2)
		*tile_step_x = -1;
	else
		*tile_step_x = 1;
}

/*
**FIXME: Calcular esto sin el cuadrado, con senos y cosenos
*/

float	get_x_intercept_length(t_ray ray, t_player_vars player)
{
	float distance;
	float x;
	float y;

	if (ray.tile_step_x == 1)
		x = ray.x_intercept - player.x;
	else
		x = player.x - ray.x_intercept;
	if (ray.tile_step_y == 1)
		y = (ray.y + 1) - player.y;
	else
		y = player.y - ray.y;
	distance = sqrtf(x * x + y * y);
	return (distance);
}

/*
** FIXME: Calcular esto sin el cuadrado, con senos y cosenos
*/

float	get_y_intercept_length(t_ray ray, t_player_vars player)
{
	float distance;
	float x;
	float y;

	if (ray.tile_step_x == 1)
		x = (ray.x + 1) - player.x;
	else
		x = player.x - ray.x;
	if (ray.tile_step_y == 1)
		y = ray.y_intercept - player.y;
	else
		y = player.y - ray.y_intercept;
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

void	check_angle_overflow(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}
