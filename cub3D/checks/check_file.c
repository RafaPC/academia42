/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:36:35 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/20 00:41:40 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

/*
** TODO: Cambiar nombre a la función
*/

t_bool		check_file(t_program_params *program_params, const char *file_path)
{
	t_list	*file_content;
	int		fd;

	file_content = NULL;
	if ((fd = check_file_path(file_path)) < 0)
		return (false);
	else if ((file_content = save_file_content(fd)) == NULL)
		return (false);
	else if (!check_file_content(file_content, program_params, 0))
	{
		ft_lstclear(&file_content, free);
		return (false);
	}
	ft_lstclear(&file_content, free);
	return (true);
}

int			check_file_path(const char *file_path)
{
	int	fd;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		print_error("Couldn't open the file");
	return (fd);
}

t_list		*save_file_content(int fd)
{
	t_list	*file_content;
	t_list	*actual_line;
	char	*aux;
	int		result;

	get_next_line(fd, &aux);
	file_content = ft_lstnew(aux);
	actual_line = file_content;
	while ((result = get_next_line(fd, &aux)) == 1)
	{
		actual_line->next = ft_lstnew(aux);
		actual_line = actual_line->next;
	}
	if (result == -1)
	{
		print_error("Error al leer el archivo");
		ft_lstclear(&file_content, free);
		return (NULL);
	}
	else
		actual_line->next = ft_lstnew(aux);
	return (file_content);
}

/*
** Sets all info id's to false
*/

void		initialice_info_ids(t_bool info_id[8])
{
	int i;

	i = 0;
	while (i < 8)
		info_id[i++] = false;
}

t_bool		check_file_content(t_list *line_elem,
t_program_params *program_params, t_info_id info_id)
{
	char	*line;
	t_bool	info_id_list[8];

	line = (char*)line_elem->content;
	initialice_info_ids(info_id_list);
	while (line && !check_info_ids(info_id_list))
	{
		if (*line)
		{
			if ((info_id = search_identifier(line)))
			{
				if (info_id_list[info_id - 1] == true)
					return (print_error("Parameter repeated"));
				info_id_list[info_id - 1] = true;
			}
			else
				return (print_error("Hay un identificador incorrecto"));
			if (!get_info(info_id, line, program_params))
				return (false);
		}
		line_elem = line_elem->next;
		line = (char*)line_elem->content;
	}
	if (!check_info_ids(info_id_list))
		return (print_error("Missing parameter in .cub file"));
	return (read_map(line_elem, program_params));
}

t_bool		check_info_ids(t_bool info_id[8])
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

t_bool		get_info(t_info_id info_id, char *line, t_program_params *params)
{
	if (info_id == id_resolution)
		return (read_resolution(line + 2, params));
	else if (info_id == id_path_north)
		return (read_path(line + 3, &(params->path_NO_texture)));
	else if (info_id == id_path_south)
		return (read_path(line + 3, &(params->path_SO_texture)));
	else if (info_id == id_path_west)
		return (read_path(line + 3, &(params->path_WE_texture)));
	else if (info_id == id_path_east)
		return (read_path(line + 3, &(params->path_EA_texture)));
	else if (info_id == id_path_sprite)
		return (read_path(line + 2, &(params->path_sprite_texture)));
	else if (info_id == id_color_floor)
		return (read_color(line + 2, &params->floor_color));
	else if (info_id == id_color_ceilling)
		return (read_color(line + 2, &params->ceilling_color));
	return (print_error("Error indefinido"));
}

void		initialice_program_params(t_program_params *program_params)
{
	program_params->path_NO_texture = NULL;
	program_params->path_SO_texture = NULL;
	program_params->path_WE_texture = NULL;
	program_params->path_EA_texture = NULL;
	program_params->path_sprite_texture = NULL;
	program_params->map = NULL;
	program_params->player_angle = -1;
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
