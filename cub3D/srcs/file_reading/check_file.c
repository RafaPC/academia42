/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:36:35 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 13:24:39 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "cub3d.h"
#include "libft.h"

/*
**			Saves the file content and search for the required information
*/

t_bool		get_cub_data(t_program_params *program_params,
const char *file_path)
{
	t_list	*file_content;
	t_bool	info_id_list[8];

	file_content = NULL;
	if (!(save_file_lines(&file_content, file_path)))
		return (false);
	initialice_info_ids(info_id_list);
	if (!read_file_lines(file_content, program_params, 0, info_id_list))
	{
		ft_lstclear(&file_content, free);
		return (false);
	}
	ft_lstclear(&file_content, free);
	return (true);
}

/*
**			Stores all the .cub file lines in an allocated struct
*/

t_bool		save_file_lines(t_list **file_content, const char *file_path)
{
	t_list	*actual_line;
	char	*aux;
	int		result;
	int		fd;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		return (print_error("Couldn't open the file"));
	get_next_line(fd, &aux);
	*file_content = ft_lstnew(aux);
	actual_line = *file_content;
	while ((result = get_next_line(fd, &aux)) == 1)
	{
		actual_line->next = ft_lstnew(aux);
		actual_line = actual_line->next;
	}
	if (result == -1)
	{
		ft_lstclear(file_content, free);
		return (print_error("Error while reading the .cub file"));
	}
	else
		actual_line->next = ft_lstnew(aux);
	return (true);
}

/*
**			Iterates through the file lines searching for each element
**			identifier, checking there are no repeated or wrong identifiers
**			and saving their information
*/

t_bool		read_file_lines(t_list *line_elem,
t_program_params *program_params, t_info_id info_id, t_bool info_id_list[10])
{
	char	*line;

	line = (char*)line_elem->content;
	while (line_elem && !check_info_ids(info_id_list))
	{
		line = (char*)line_elem->content;
		if (*line)
		{
			if ((info_id = search_identifier(line)))
			{
				if (info_id_list[info_id - 1] == true)
					return (print_error("Parameter repeated"));
				info_id_list[info_id - 1] = true;
			}
			else
				return (print_error("Wrong identifier"));
			if (!get_info(info_id, line, program_params))
				return (false);
		}
		line_elem = line_elem->next;
	}
	if (!check_info_ids(info_id_list))
		return (print_error("Missing parameter in .cub file"));
	return (read_map(line_elem, program_params));
}

/*
**			Checks the info id and calls the appropiate function
*/

t_bool		get_info(t_info_id info_id, char *line, t_program_params *params)
{
	if (info_id == id_resolution)
		return (read_resolution(line + 2, params));
	else if (info_id == id_path_north)
		return (read_path(line + 3, &(params->path_north_texture)));
	else if (info_id == id_path_south)
		return (read_path(line + 3, &(params->path_south_texture)));
	else if (info_id == id_path_west)
		return (read_path(line + 3, &(params->path_west_texture)));
	else if (info_id == id_path_east)
		return (read_path(line + 3, &(params->path_east_texture)));
	else if (info_id == id_path_sprite)
		return (read_path(line + 2, &(params->path_sprite_texture)));
	else if (info_id == id_color_floor)
		return (read_color(line + 2, &params->floor_color));
	else if (info_id == id_color_ceilling)
		return (read_color(line + 2, &params->ceilling_color));
	return (print_error("Undefined error"));
}

/*
**			Compares the first charcters of the line with every identifier
**			and returns the correct identifier id
*/

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
