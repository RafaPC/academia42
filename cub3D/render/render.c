/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/28 16:41:14 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

int		render_screen(t_vars *vars)
{
	check_movement(vars);
	if (is_moving(vars->keys_pressed))
	{
		raycast(vars);
		// draw_map(vars);
		// draw_player(vars);
		render_sprites(vars);
		mlx_put_image_to_window(
			vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
	}
	return (0);
}

void	render_column(t_vars *vars, float distance, float wall_x, int x_coord)
{
	int		column_height;
	int		starting_position;
	float	i;

	column_height = (int)(vars->max_col_height / distance);
		render_ceil_and_floor(vars, x_coord, column_height);
	
	starting_position  = vars->screen_height / 2 - column_height / 2 + vars->y_offset;
	i = starting_position < 0 ? -starting_position : 0;
	while ((int)i++ < column_height && starting_position + (int)i < vars->screen_height)
	{	
		my_mlx_pixel_put(vars->mlx.img, x_coord, starting_position + i,
			get_wall_color(vars, wall_x, i / column_height));
	}
}

void	render_ceil_and_floor(t_vars *vars, int x_coord, int column_height)
{
	int start_floor;
	int end_ceiling;

	end_ceiling = vars->screen_height / 2 + vars->y_offset;
	if (end_ceiling > vars->screen_height)
		end_ceiling = vars->screen_height;
	draw_square(get_coords_struct(x_coord, 0, x_coord, end_ceiling),
		vars->ceiling_color, vars->mlx.img);
	start_floor = vars->screen_height / 2 + vars->y_offset;
	if (start_floor < 0)
		start_floor = 0;
	draw_square(get_coords_struct(x_coord, start_floor, x_coord, vars->screen_height),
		vars->floor_color, vars->mlx.img);
}
