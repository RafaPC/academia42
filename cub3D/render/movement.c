/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:10:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/26 17:12:44 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	move(t_player_vars *player, char **map, float angle, float velocity)
{
	float	new_x;
	float	new_y;
	float	pdx;
	float	pdy;

	check_angle_overflow(&angle);
	pdx = cosf(angle);
	pdy = sinf(angle);
	new_x = player->x + pdx * (0.3 * velocity);
	new_y = player->y - pdy * (0.3 * velocity);
	if (map[(int)new_y][(int)player->x] == '1')
	{
		if (map[(int)player->y][(int)new_x] != '1')
			player->x += pdx * (0.05 * velocity);
	}
	else
		player->y -= pdy * (0.1 * velocity);
	if (map[(int)player->y][(int)new_x] == '1')
	{
		if (map[(int)new_y][(int)player->x] != '1')
			player->y -= pdy * (0.05 * velocity);
	}
	else
		player->x += pdx * (0.1 * velocity);
}

void	check_movement(t_vars *vars)
{
	if (vars->keys_pressed.left_arrow)
	{
		vars->player.angle += 0.1;
		if (vars->player.angle > 2 * PI)
			vars->player.angle -= 2 * PI;
		vars->player.dx = cosf(vars->player.angle);
		vars->player.dy = sinf(vars->player.angle);
	}
	if (vars->keys_pressed.right_arrow)
	{
		vars->player.angle -= 0.1;
		if (vars->player.angle < 0)
			vars->player.angle += 2 * PI;
		vars->player.dx = cosf(vars->player.angle);
		vars->player.dy = sinf(vars->player.angle);
	}
	if (vars->keys_pressed.w)
		move(&vars->player, vars->map, vars->player.angle, 1);
	if (vars->keys_pressed.a)
		move(&vars->player, vars->map, vars->player.angle + PI / 2, 0.3);
	if (vars->keys_pressed.s)
		move(&vars->player, vars->map, vars->player.angle - PI, 0.5);
	if (vars->keys_pressed.d)
		move(&vars->player, vars->map, vars->player.angle - PI / 2, 0.3);
}

t_bool	is_moving(t_keys keys)
{
	if (keys.w || keys.a || keys.s || keys.d ||
	keys.left_arrow || keys.right_arrow)
		return (true);
	else
		return (false);
}