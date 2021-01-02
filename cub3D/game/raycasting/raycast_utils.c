/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:22:48 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/30 16:29:44 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
**	Get x intercept length
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
**	Get y intercept length
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
**	Check if the given angle is under 0 or over 2PI and corrects it
*/

void	check_angle_overflow(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

/*
**		Sets the tile in which the shortest distance ends
*/

void	set_tile_crossed(t_ray *ray, char **map)
{
	if (ray->distance_hor < ray->distance_ver)
		ray->tile_crossed = map[(int)ray->y + ray->tile_step_y]
		[(int)ray->x_intercept];
	else
		ray->tile_crossed = map[(int)ray->y_intercept]
		[(int)ray->x + ray->tile_step_x];
}

/*
**		Checks if the ray goes throught a sprite
*/

void	check_sprite_crossed(t_ray ray, char tile_crossed, t_vars *vars)
{
	t_texture sprite_texture;

	if (tile_crossed == '2' || tile_crossed == '3' || tile_crossed == '4')
	{
		if (tile_crossed == '2')
			sprite_texture = vars->textures.sprite_1;
		else if (tile_crossed == '3')
			sprite_texture = vars->textures.sprite_2;
		else
			sprite_texture = vars->textures.sprite_3;
		if (ray.direction == horizontal)
			add_sprite_coords(floorf(ray.x_intercept) + 0.5,
				ray.y + ray.tile_step_y + 0.5, vars, sprite_texture);
		else if (ray.direction == vertical)
			add_sprite_coords((int)ray.x + ray.tile_step_x + 0.5,
				floorf(ray.y_intercept) + 0.5, vars, sprite_texture);
	}
}
