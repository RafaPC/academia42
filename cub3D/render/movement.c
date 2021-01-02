/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:10:49 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/02 02:36:16 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <math.h>

/*
**		Moves the player in an angle with a determined velocity
**		checking collisions
*/

void	move(t_player_vars *player, char **map, float angle, float velocity)
{
	int		new_x;
	int		new_y;
	float	pdx;
	float	pdy;

	check_angle_overflow(&angle);
	pdx = cosf(angle);
	pdy = sinf(angle);
	new_x = player->x + pdx * (0.3 * velocity);
	new_y = player->y - pdy * (0.3 * velocity);
	if (blocks_movement(map[new_y][(int)player->x]))
	{
		if (!blocks_movement(map[(int)player->y][new_x]))
			player->x += pdx * (0.05 * velocity);
	}
	else
		player->y -= pdy * (0.1 * velocity);
	if (blocks_movement(map[(int)player->y][new_x]))
	{
		if (!blocks_movement(map[new_y][(int)player->x]))
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
	if (x > 0 && x < vars->window_width && y > 0 && y < vars->window_height &&
	x != vars->mouse_x)
	{
		vars->keys_pressed.mouse_moved = true;
		if (x > vars->mouse_x + 2)
			vars->player.angle -= 0.1;
		else if (x < vars->mouse_x - 2)
			vars->player.angle += 0.1;
		check_angle_overflow(&vars->player.angle);
		vars->player.dx = cosf(vars->player.angle);
		vars->player.dy = sinf(vars->player.angle);
		if (y < vars->mouse_y - 1)
			vars->y_offset += 20;
		else if (y > vars->mouse_y + 1)
			vars->y_offset -= 20;
		vars->mouse_x = x;
		vars->mouse_y = y;
	}
	else
		vars->keys_pressed.mouse_moved = false;
}

/*
**		Checks for keyboard/mouse input and changes
**		the position, y_offset and angle accordingly
*/

void	check_movement(t_vars *vars, t_keys keys)
{
	check_mouse_move(vars);
	if (keys.left_arrow)
		vars->player.angle += 0.1;
	else if (keys.right_arrow)
		vars->player.angle -= 0.1;
	check_angle_overflow(&vars->player.angle);
	vars->player.dx = cosf(vars->player.angle);
	vars->player.dy = sinf(vars->player.angle);
	if (keys.up_arrow && vars->y_offset < vars->window_height / 2)
		vars->y_offset += (vars->window_height / 2) / 20;
	if (keys.down_arrow && vars->y_offset > -vars->window_height / 2)
		vars->y_offset -= (vars->window_height / 2) / 20;
	if (keys.w)
		move(&vars->player, vars->map, vars->player.angle, 1);
	if (keys.a)
		move(&vars->player, vars->map, vars->player.angle + PI / 2, 0.3);
	if (keys.s)
		move(&vars->player, vars->map, vars->player.angle - PI, 0.5);
	if (keys.d)
		move(&vars->player, vars->map, vars->player.angle - PI / 2, 0.3);
	if (vars->map[(int)vars->player.y][(int)vars->player.x] == '4')
	{
		vars->map[(int)vars->player.y][(int)vars->player.x] = '0';
		vars->score++;
	}
}

/*
**		Returns true if any of the inputs is set to true
*/

t_bool	is_moving(t_keys keys)
{
	if (keys.w || keys.a || keys.s || keys.d ||
	keys.left_arrow || keys.right_arrow || keys.up_arrow || keys.down_arrow
	|| keys.mouse_moved)
		return (true);
	else
		return (false);
}

/*
**		Receives a map character and returns true if
**		that character has collisions
*/

t_bool	blocks_movement(char c)
{
	if (c == '1' || c == '2' || c == '3')
		return (true);
	else
		return (false);
}
