/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:07:12 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/18 19:04:14 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

/*
**		Frees all the textures
*/

void	free_textures(t_vars *vars)
{
	if (vars->textureN.data.img)
		mlx_destroy_image(vars->mlx.mlx, vars->textureN.data.img);
	if (vars->textureS.data.img)
		mlx_destroy_image(vars->mlx.mlx, vars->textureS.data.img);
	if (vars->textureE.data.img)
		mlx_destroy_image(vars->mlx.mlx, vars->textureE.data.img);
	if (vars->textureW.data.img)
		mlx_destroy_image(vars->mlx.mlx, vars->textureW.data.img);
	if (vars->textureSprite.data.img)
		mlx_destroy_image(vars->mlx.mlx, vars->textureSprite.data.img);
}

void	free_memory(t_vars *vars)
{
	free_textures(vars);
	free_map(vars->map);
	if (vars->distances)
		free(vars->distances);
	ft_lstclear(&vars->sprite, free);
	//Cosas de la minilibx
	mlx_destroy_image(vars->mlx.mlx, vars->mlx.img->img);
	if (vars->mlx.img)
		free(vars->mlx.img);
	mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	mlx_destroy_display(vars->mlx.mlx);
	free(vars->mlx.mlx);
}

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
