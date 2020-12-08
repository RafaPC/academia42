/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:56:47 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/08 02:07:58 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	t_bool	correct;

	correct = true;
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

//TODO: checkear la funcion en sí
t_bool	read_color(t_error_info *error_info, char *line, int *color)
{
	int		colors[3];

	while (*line == ' ')
		line++;
	if (!check_color_characters(line))
		return (raise_error(error_info, color_wrong_character));
	colors[0] = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	line++;
	colors[1] = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	line++;
	colors[2] = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0')
		raise_error(error_info, color_wrong_character);
	if (!check_colors_min_max(colors))
		raise_error(error_info, color_wrong_value);
	color = create_trgb(0, colors[0], colors[1], colors[2]);
	return (true);
}

//Checkea los cáracteres de la línea donde se define un color, solo puede haber números, espacios y comas
t_bool check_color_characters(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != ',' && !ft_isdigit(*line))
			return (false);
		line++;
	}
	return (true);
}

t_bool check_colors_min_max(int colors[3])
{
	int i = 0;
	while (i < 3)
	{
		if (colors[i] < 0 || colors[i] > 255)
			return (false);
		i++;
	}
		return (true);
}
