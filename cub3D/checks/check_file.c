/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:36:35 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/10 17:54:34 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

//TODO: Cambiar nombre a la función
t_bool	check_file(t_error_info *error_info, t_program_params *program_params, const char *file_path)
{
	t_list	*file_content;
	int 	fd;

	initialice_program_params(program_params);
	file_content = NULL;
	if ((fd = check_file_path(error_info, file_path)) < 0)
		return (raise_error(error_info, open_file_error));
	else if ((file_content = save_file_content(error_info, fd)) == NULL)
		return (raise_error(error_info, read_file_error));
	else if (!check_file_content(error_info, file_content, program_params))
	{
		ft_lstclear(&file_content, free);
		return (false);
	}
	ft_lstclear(&file_content, free);
	return (true);
}

int		check_file_path(t_error_info *error_info, const char *file_path)
{
	int	fd;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		error_info->error_type = open_file_error;
	return (fd);
}

t_list	*save_file_content(t_error_info *error_info, int fd)
{
	t_list	*file_content;
	t_list	*actual_line;
	char	*aux;
	int 	result;

	get_next_line(fd, &aux);
	file_content = ft_lstnew(aux);
	actual_line = file_content;
	while((result = get_next_line(fd, &aux)) == 1)
	{
		actual_line->next = ft_lstnew(aux);
		actual_line = actual_line->next;
	}
	if (result == -1)
	{
		error_info->error_type = read_file_error;
		ft_lstclear(&file_content, free);
		return (NULL);
	}
	else
		actual_line->next = ft_lstnew(aux);
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


t_bool		check_file_content(t_error_info *error_info, t_list *file_content,
t_program_params *program_params)
{
	t_list	*line;
	t_bool	info_id_list[8];
	t_info_id info_id;

	line = file_content;
	info_id = -1;
	initialice_info_ids(info_id_list);
	while (!check_info_ids(info_id_list))
	{
		if (*((char*)line->content))
		{
			if ((info_id = search_identifier(line->content)))
			{
				if (info_id_list[info_id - 1] == true) //Si ya se ha leído ese identificador, ERROR está duplicado
					return (raise_error(error_info, duplicated_info_error));
				info_id_list[info_id - 1] = true;
			}
			else
				return (raise_error(error_info, wrong_identifier_error));
			if (!get_info(info_id, error_info, line->content, program_params))
				return (print_error(error_info));
		}
		else
			return (raise_error(error_info, missing_information_error)); //Si entra aquí ha acabado el archivo y no ha encontrado toda la información
		line = line->next;
	}
	if (!read_map(error_info, line, program_params))
		return (false);
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
		return (read_resolution(error_info, line + 2, params));
	else if (info_id == id_path_north)
		return (read_path(error_info, line + 3, &(params->path_NO_texture)));
	else if (info_id == id_path_south)
		return (read_path(error_info, line + 3, &(params->path_SO_texture)));
	else if (info_id == id_path_west)
		return (read_path(error_info, line + 3, &(params->path_WE_texture)));
	else if (info_id == id_path_east)
		return (read_path(error_info, line + 3, &(params->path_EA_texture)));
	else if (info_id == id_path_sprite)
		return (read_path(error_info, line + 2, &(params->path_sprite_texture)));
	else if (info_id == id_color_floor)
		return (read_color(error_info, line + 2, &params->floor_color));
	else if (info_id == id_color_ceilling)
		return (read_color(error_info, line + 2, &params->ceilling_color));
	//TODO:Maybe añadir un código de error aunque nunca debería llegar a este return
	return (false);
}

//Si dejo lo de las ids ni necesito esto
void	initialice_program_params(t_program_params *program_params)
{
	program_params->resolution_x = -1;
	program_params->resolution_y = -1;
	program_params->path_NO_texture = NULL;
	program_params->path_SO_texture = NULL;
	program_params->path_WE_texture = NULL;
	program_params->path_EA_texture = NULL;
	program_params->path_sprite_texture = NULL;
	program_params->floor_color = -1;
	program_params->ceilling_color = -1;
	program_params->map = NULL;
}

t_info_id	search_identifier(char *line)
{
	t_info_id id;

	id = 0;
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
