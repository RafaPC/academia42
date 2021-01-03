/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:07:12 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 20:36:57 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

/*
**		Calls functions to free the textures and the map
**		and the appropiate mlx functions to free memory
*/

void	free_and_close(t_vars *vars)
{
	if (vars->mlx.mlx)
		free_textures(vars->mlx.mlx, vars->textures);
	if (vars->map)
		free_map(vars->map);
	if (vars->distances)
		free(vars->distances);
	ft_lstclear(&vars->sprite, free);
	if (vars->mlx.img)
		mlx_destroy_image(vars->mlx.mlx, vars->mlx.img->img);
	if (vars->mlx.img)
		free(vars->mlx.img);
	if (vars->mlx.win)
		mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	if (vars->mlx.mlx)
		mlx_destroy_display(vars->mlx.mlx);
	if (vars->mlx.mlx)
		free(vars->mlx.mlx);
	exit(0);
}

/*
**		Frees all the loaded textures
*/

void	free_textures(void *mlx, t_textures textures)
{
	if (textures.wall_north.data.img)
		mlx_destroy_image(mlx, textures.wall_north.data.img);
	if (textures.wall_south.data.img)
		mlx_destroy_image(mlx, textures.wall_south.data.img);
	if (textures.wall_east.data.img)
		mlx_destroy_image(mlx, textures.wall_east.data.img);
	if (textures.wall_west.data.img)
		mlx_destroy_image(mlx, textures.wall_west.data.img);
	if (textures.sprite.data.img)
		mlx_destroy_image(mlx, textures.sprite.data.img);
}

/*
**		Frees the allocated char pointers of the map
*/

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map[i]);
	free(map);
}

/*
**		This function is only called if it encounters a
**		discrepancy in the .cub file
*/

void	free_program_params(t_program_params params)
{
	if (params.path_north_texture)
		free(params.path_north_texture);
	if (params.path_south_texture)
		free(params.path_south_texture);
	if (params.path_east_texture)
		free(params.path_east_texture);
	if (params.path_west_texture)
		free(params.path_west_texture);
	if (params.path_sprite_texture)
		free(params.path_sprite_texture);
}
