/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:36:35 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/07 12:53:21 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

//TODO: Cambiar nombre a la función
t_bool	check_file(t_error_info *error_info, t_program_params *program_params, char *file_path)
{
	t_line				*file_content;
	int 	fd;

	initialice_program_params(program_params);
	file_content = NULL;
	if ((fd = check_file_path(error_info, file_path)) < 0)
		return (raise_error(error_info, open_file_error));
	else if (!(file_content = save_file_content(error_info, fd)))
		return (raise_error(error_info, read_file_error));
	else if (!check_file_content(error_info, file_content, program_params))
		return (false);
	return (true);
}

int		check_file_path(t_error_info *error_info, char *file_path)
{
	int	fd;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		error_info->error_type = open_file_error;
	return (fd);
}

t_line	*save_file_content(t_error_info *error_info, int fd)
{
	t_line	*file_content;
	t_line	*actual_line;
	char	*aux;
	int 	result;

	file_content = (t_line*)malloc(sizeof(t_line));
	actual_line = file_content;
	while((result = get_next_line(fd, &aux)) == 1)
	{
		actual_line->line = aux;
		actual_line->next_line = (t_line*)malloc(sizeof(t_line));
		actual_line = actual_line->next_line;
	}
	if (result == -1)
	{
		error_info->error_type = read_file_error;
		//TODO: Liberar memoria y poner el mapa a nulo
	}
	else
	{
		actual_line->line = aux;
		actual_line->next_line = NULL;
	}
	return (file_content);
}

//Sets all info id's to false
void	initialice_info_ids(t_bool info_id[8])
{
	int i;

	i = 0;
	while (i < 8)
		info_id[i++] = false;
}


t_bool		check_file_content(t_error_info *error_info, t_line *file_content,
t_program_params *program_params)
{
	t_line	*line;
	t_bool	info_id_list[8];
	t_info_id info_id;

	line = file_content;
	info_id = -1;
	initialice_info_ids(info_id_list);
	while (!check_info_ids(info_id_list))
	{
		if (*(line->line))
		{
			if ((info_id = search_identifier(line->line)) != -1)
			{
				if (info_id_list[info_id] == true) //Si ya se ha leído ese identificador, ERROR está duplicado
					return (raise_error(error_info, duplicated_info_error));
				info_id_list[info_id] = true;
			}
			else
				return (raise_error(error_info, wrong_identifier_error));
			if (!get_info(info_id, error_info, line->line, program_params))
				return (print_error(error_info));
		}
		line = line->next_line;
	}
	return (true);

}

t_bool	check_info_ids(t_bool info_id[8])
{
	int		i;
	t_bool completed;
	
	i = 0;
	completed = true;
	while (i < 8 && completed)
	{
		if (info_id[i++] == false)
			completed = false;
	}
	return (completed);
}

t_bool		get_info(t_info_id info_id, t_error_info *error_info, char *line, t_program_params *params)
{
	if (info_id == id_resolution)
		return (read_resolution(error_info + 1, line, params));
	else if (info_id == id_path_north)
		return (read_path(error_info, line + 1, &(params->path_NO_texture)));
	else if (info_id == id_path_south)
		return (read_path(error_info, line + 1, &(params->path_SO_texture)));
	else if (info_id == id_path_west)
		return (read_path(error_info, line + 1, &(params->path_WE_texture)));
	else if (info_id == id_path_east)
		return (read_path(error_info, line + 1, &(params->path_EA_texture)));
	else if (info_id == id_path_sprite)
		return (read_path(error_info, line, &(params->path_sprite_texture)));
	else if (info_id == id_color_floor)
		return (read_color(error_info, line + 1, params->floor_color));
	else if (info_id == id_color_ceilling)
		return (read_color(error_info, line + 1, params->ceilling_color));
	return (false);
}

void	initialice_program_params(t_program_params *program_params)
{
	program_params->resolution_x = -1;
	program_params->resolution_y = -1;
	program_params->path_NO_texture = NULL;
	program_params->path_SO_texture = NULL;
	program_params->path_WE_texture = NULL;
	program_params->path_EA_texture = NULL;
	program_params->path_sprite_texture = NULL;
	program_params->floor_color = NULL;
	program_params->ceilling_color = NULL;
}

t_info_id	search_identifier(char *line)
{
	t_info_id id;

	id = -1;
	if (ft_strncmp(line, "R ", 2) == 0)
		id = id_resolution;
	else if (ft_strncmp(line, "NO ", 3) == 0)
		id = id_path_north;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		id = id_path_south;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		id = id_path_west;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		id = id_path_east;
	else if (ft_strncmp(line, "S ", 2) == 0)
		id = id_path_sprite;
	else if (ft_strncmp(line, "F ", 2) == 0)
		id = id_color_floor;
	else if (ft_strncmp(line, "C ", 2) == 0)
		id = id_color_ceilling;
	return (id);
}
