/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:38:49 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/31 17:32:34 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include "libft.h"

/*
**		Write the amount of score at the top left corner of the screen
*/

void	display_score(t_vars vars)
{
	char	*score;
	char	*aux;

	score = "SCORE: ";
	aux = ft_itoa(vars.score);
	score = ft_strjoin(score, aux);
	mlx_string_put(vars.mlx.mlx, vars.mlx.win, 5, 20, WALL_COLOR, score);
	free(score);
	free(aux);
}

/*
**		Function that gets called all the time while the program runs
**		It only redraw the screen if any input is entered
**		and the screen should change
*/

int		render_screen(t_vars *vars)
{
	check_movement(vars, vars->keys_pressed);
	if (is_moving(vars->keys_pressed))
	{
		raycast(vars);
		render_sprites(vars);
		mlx_put_image_to_window(
			vars->mlx.mlx, vars->mlx.win, vars->mlx.img->img, 0, 0);
		display_score(*vars);
	}
	return (0);
}

/*
**		Renders one column of the window
*/

void	render_column(t_vars *vars, float distance, float wall_x, int x_coord)
{
	int		column_height;
	int		starting_position;
	float	i;

	column_height = (int)(vars->max_col_height / distance);
	render_ceil_and_floor(vars, x_coord);
	starting_position = vars->window_height / 2 - column_height / 2 +
		vars->y_offset;
	i = starting_position < 0 ? -starting_position : 0;
	while ((int)i++ < column_height &&
	starting_position + (int)i < vars->window_height)
	{
		my_mlx_pixel_put(vars->mlx.img, x_coord, starting_position + i,
			add_shade(distance, get_wall_color(vars->textures,
				vars->wall_face, wall_x, i / column_height)));
	}
}

/*
**		Renders the ceil and floor for one column of the window
*/

void	render_ceil_and_floor(t_vars *vars, int x_coord)
{
	int start_floor;
	int end_ceiling;

	end_ceiling = vars->window_height / 2 + vars->y_offset;
	if (end_ceiling > vars->window_height)
		end_ceiling = vars->window_height;
	draw_square(get_coords_struct(x_coord, 0, x_coord, end_ceiling),
		vars->ceiling_color, vars->mlx.img);
	start_floor = vars->window_height / 2 + vars->y_offset;
	if (start_floor < 0)
		start_floor = 0;
	draw_square(
		get_coords_struct(x_coord, start_floor, x_coord, vars->window_height),
		vars->floor_color, vars->mlx.img);
}
