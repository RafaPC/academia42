/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:10:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/16 16:41:32 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	move(t_player_vars *player, char **map, float angle, float velocity)
{	 
	float	newX;
	float	newY;
	float	pdx;
	float	pdy;

	check_angle_overflow(&angle);
	pdx = cosf(angle);
	pdy = sinf(angle);
	newX = player->x + pdx * (0.3 * velocity);
	newY = player->y - pdy * (0.3 * velocity);
	if (map[(int)newY][(int)player->x] == '1')
	{
		if (map[(int)player->y][(int)newX] != '1')
			player->x += pdx * (0.05 * velocity);
	}
	else
		player->y -= pdy * (0.1 * velocity);
	
	if (map[(int)player->y][(int)newX] == '1')
	{
		if (map[(int)newY][(int)player->x] != '1')
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
		move(&vars->player, vars->map, vars->player.angle + PI/2, 0.3);
	if (vars->keys_pressed.s)
		move(&vars->player, vars->map, vars->player.angle - PI, 0.5);
	if (vars->keys_pressed.d)
		move(&vars->player, vars->map, vars->player.angle - PI/2, 0.3);
}
