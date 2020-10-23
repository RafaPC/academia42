/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:36:35 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/22 12:56:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

t_bool	check_map(t_error_info *error_info, char *file_path)
{
	t_line				*file_content;
	t_program_params	*program_params;
	int 	fd;

	file_content = NULL;
	if ((fd = check_file_path(error_info, file_path)) < 0)
		return (print_error(error_info));
	if (!(file_content = save_file_content(error_info, file_content, fd)))
		return (print_error(error_info));
	if (!check_file_content(error_info, file_content, program_params))
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

t_line	*save_file_content(t_error_info *error_info, t_line *file_content, int fd)
{
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
		//Liberar memoria y poner el mapa a nulo
	}
	else
	{
		actual_line->line = aux;
		actual_line->next_line = NULL;
	}
	return (file_content);
}

t_bool		print_error(t_error_info *error_info)
{
	//Here reads the error type and prints it
	return (false);
}

t_bool		check_file_content(t_error_info *error_info, t_line *file_content,
t_program_params *program_params)
{
	t_line	*line;
	if (!check_resolution(error_info, line->line, program_params))
		return (false);
}
