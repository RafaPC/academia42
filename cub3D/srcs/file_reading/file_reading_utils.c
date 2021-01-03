/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:50:31 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 12:55:09 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"

/*
**		Initialices pointer valuest to NULL to be able to check
**		against NULL before freeing each pointer
**		Player angle is initialiced to negative value to check against
**		it and see if there are more than 1 player position definition
**		characters (N, S, E, W) in the map
*/

void	initialice_program_params(t_program_params *program_params)
{
	program_params->path_north_texture = NULL;
	program_params->path_south_texture = NULL;
	program_params->path_west_texture = NULL;
	program_params->path_east_texture = NULL;
	program_params->path_sprite_texture = NULL;
	program_params->map = NULL;
	program_params->player_angle = -1;
}

/*
**		Sets all info id's to false
*/

void	initialice_info_ids(t_bool info_id_list[8])
{
	int i;

	i = 0;
	while (i < 8)
		info_id_list[i++] = false;
}

/*
**		Returns true if all the info ids are set to true
**		Returns false if not
*/

t_bool	check_info_ids(t_bool info_id[8])
{
	int		i;
	t_bool	completed;

	i = 0;
	completed = true;
	while (i < 8 && completed)
	{
		if (info_id[i++] == false)
			completed = false;
	}
	return (completed);
}

/*
**		Receives a string and prints it with "Error\n" before it
*/

t_bool	print_error(const char *msg)
{
	ft_printf("Error\n%s\n", msg);
	return (false);
}
