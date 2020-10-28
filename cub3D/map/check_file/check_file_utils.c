/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:56:47 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/27 12:07:24 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
// #include "../../libft/include/libft.h"

t_bool	read_resolution(t_error_info *error_info, char *line,
t_program_params *program_params)
{
	t_bool	correct;

	correct = true;
	line++;
	while (*line == ' ')
		line++;
	program_params->resolution_x = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
	while(ft_isspace(*line))
		line++;
	program_params->resolution_y = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
	if (*line)
		correct = false;
	//TODO: checkeo si después del número hay nulo o más cosas, ya veré que poner
	return (correct);
}

t_bool	read_path(t_error_info *error_info, char *line, char **path_to_texture)
{
	int		i;
	t_bool	correct;

	correct = true;
	line += 2;
	while (*line == ' ')
		line++;
	if (*(line) == '.' && *(line + 1) == '/')
	{
		*path_to_texture = (char*)malloc(sizeof(char) * (ft_strlen(line) + 1));
		ft_strlcpy(*path_to_texture, line, ft_strlen(line) + 1);
	}
	else
	{
		//TODO: error wrong format
	}
	return (correct);
}

t_bool	read_color(t_error_info *error_info, char *line, int *color)
{
	return (false);
}
