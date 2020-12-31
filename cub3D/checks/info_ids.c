/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_ids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:50:31 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/31 12:59:29 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**			Initialices pointer valuest to NULL to be able to check
**			against NULL before freeing each pointer
**			Player angle is initialiced to negative value to check against
**			it and see if there are more than 1 player position definition
**			characters (N, S, E, W) in the map
*/

void		initialice_program_params(t_program_params *program_params)
{
	program_params->path_NO_texture = NULL;
	program_params->path_SO_texture = NULL;
	program_params->path_WE_texture = NULL;
	program_params->path_EA_texture = NULL;
	program_params->path_sprite_texture = NULL;
	program_params->path_sprite2_texture = NULL;
	program_params->path_sprite3_texture = NULL;
	program_params->map = NULL;
	program_params->player_angle = -1;
}

/*
**			Sets all info id's to false
*/

void		initialice_info_ids(t_bool info_id[10])
{
	int i;

	i = 0;
	while (i < 10)
		info_id[i++] = false;
}

/*
**			Returns true if all the info ids are set to true
**			Returns false if not
*/

t_bool		check_info_ids(t_bool info_id[10])
{
	int		i;
	t_bool	completed;

	i = 0;
	completed = true;
	while (i < 10 && completed)
	{
		if (info_id[i++] == false)
			completed = false;
	}
	return (completed);
}
