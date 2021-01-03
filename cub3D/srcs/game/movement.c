/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:10:49 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 13:43:48 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <math.h>

/*
**		Moves the player in an angle with a determined velocity
**		checking collisions TODO:
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
	if (!blocks_movement(map[new_y][new_x]))
	{
		player->x += pdx * (0.1 * velocity);
		player->y -= pdy * (0.1 * velocity);	
	}
}

/*
**		Checks for keyboard/mouse input and changes
**		the position, y_offset and angle accordingly
*/

void	check_movement(t_vars *vars, t_keys keys)
{
	if (keys.left_arrow)
		vars->player.angle += 0.1;
	else if (keys.right_arrow)
		vars->player.angle -= 0.1;
	check_angle_overflow(&vars->player.angle);
	vars->player.dx = cosf(vars->player.angle);
	vars->player.dy = sinf(vars->player.angle);
	if (keys.w)
		move(&vars->player, vars->map, vars->player.angle, 1);
	if (keys.a)
		move(&vars->player, vars->map, vars->player.angle + PI / 2, 0.3);
	if (keys.s)
		move(&vars->player, vars->map, vars->player.angle - PI, 0.5);
	if (keys.d)
		move(&vars->player, vars->map, vars->player.angle - PI / 2, 0.3);
}

/*
**		Returns true if any of the inputs is set to true
*/

t_bool	is_moving(t_keys keys)
{
	if (keys.left_arrow || keys.right_arrow ||
		keys.w || keys.a || keys.s || keys.d)
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
	if (c == '1' || c == '2')
		return (true);
	else
		return (false);
}
