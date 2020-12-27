/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:10:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/27 12:24:24 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d.h"
#include <math.h>

t_bool	blocks_movement(char c)
{
	if (c == '1' || c == '2')
		return (true);
	else
		return (false);
}

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
	if (blocks_movement(map[(int)new_y][(int)player->x]))
	{
		if (blocks_movement(map[(int)player->y][(int)new_x]))
			player->x += pdx * (0.05 * velocity);
	}
	else
		player->y -= pdy * (0.1 * velocity);
	if (blocks_movement(map[(int)player->y][(int)new_x]))
	{
		if (blocks_movement(map[(int)new_y][(int)player->x]))
			player->y -= pdy * (0.05 * velocity);
	}
	else
		player->x += pdx * (0.1 * velocity);
}

/*
**		Checks wether the mouse is in the window and has moved
**		to the right or left respective to its last position
*/

void	check_mouse_move(t_vars *vars)
{
	int x;
	int y;

	mlx_mouse_get_pos(vars->mlx.mlx, vars->mlx.win, &x, &y);	
	if (x > 0 && x < vars->screen_width && y > 0 && y < vars->screen_height &&
	x != vars->mouse_x)
	{
		vars->keys_pressed.mouse_moved = true;
		if (x > vars->mouse_x)
		{
			vars->player.angle -= 0.1;
			if (vars->player.angle < 0)
				vars->player.angle += 2 * PI;
			vars->player.dx = cosf(vars->player.angle);
			vars->player.dy = sinf(vars->player.angle);
		}
		else if (x < vars->mouse_x)
		{
			vars->player.angle += 0.1;
			if (vars->player.angle > 2 * PI)
				vars->player.angle -= 2 * PI;
			vars->player.dx = cosf(vars->player.angle);
			vars->player.dy = sinf(vars->player.angle);
		}
		vars->mouse_x = x;
	}
	else
		vars->keys_pressed.mouse_moved = false;
}


void	check_movement(t_vars *vars)
{
	check_mouse_move(vars);
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
	keys.left_arrow || keys.right_arrow || keys.mouse_moved)
		return (true);
	else
		return (false);
}
