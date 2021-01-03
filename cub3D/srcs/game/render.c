/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 17:56:54 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include "libft.h"

/*
**		Calls the appropiate functions to render one frame
*/

void	render_once(t_vars *vars)
{
	raycast(vars);
	render_sprites(vars);
	mlx_put_image_to_window(
			vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
}

/*
**		Function that gets called all the time while the program runs
**		It only redraw the screen if any input is entered
**		and the screen should change
*/

int		render_screen(t_vars *vars)
{
	if (is_moving(vars->keys_pressed))
	{
		check_movement(vars, vars->keys_pressed);
		render_once(vars);
	}
	return (0);
}

/*
**		Renders one column of the window
*/

void	render_column(t_vars *vars, float distance, float wall_x, int window_x)
{
	int		column_height;
	int		y_start;
	int		y;

	column_height = (int)(vars->max_col_height / distance);
	render_ceil_and_floor(vars, window_x);
	y_start = vars->window_height / 2 - column_height / 2;
	y = y_start < 0 ? -y_start : 0;
	while (y < column_height && y_start + y < vars->window_height)
	{
		put_pixel(vars->mlx.img, window_x, y_start + y,
		get_wall_color(vars->textures,
				vars->wall_face, wall_x, (float)y / column_height));
		y++;
	}
}

/*
**		Renders the ceil and floor for one column of the window
*/

void	render_ceil_and_floor(t_vars *vars, int x_coord)
{
	draw_square(
		get_coords_struct(x_coord, 0, x_coord, vars->window_height / 2),
		vars->ceiling_color, vars->mlx.img);
	draw_square(
		get_coords_struct(x_coord, vars->window_height / 2, x_coord,
		vars->window_height), vars->floor_color, vars->mlx.img);
}
