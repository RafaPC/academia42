/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:56:47 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/30 17:02:23 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	read_resolution(char *line, t_program_params *program_params)
{
	t_bool	correct;

	correct = true;
	while (*line == ' ')
		line++;
	program_params->window_width = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	program_params->window_height = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (!(ft_isdigit(*(line - 1)) && *line == '\0'))
		return (print_error("Carácter inválido en la resolución"));
	return (correct);
}

t_bool	read_path(char *line, char **path_to_texture)
{
	t_bool	correct;
	int		path_length;

	correct = true;
	while (*line == ' ')
		line++;
	if (*(line) == '.' && *(line + 1) == '/')
	{
		path_length = ft_strlen(line);
		*path_to_texture = (char*)malloc(sizeof(char) * (path_length + 1));
		ft_strlcpy(*path_to_texture, line, path_length + 1);
		if (ft_strncmp("XPM", &(*path_to_texture)[path_length - 3], 3)
		&& ft_strncmp("xpm", &(*path_to_texture)[path_length - 3], 3))
			return (print_error(
				"Extensión incorrecta del archivo dado por parámetro"));
	}
	else
		return (print_error("Formato del path incorrecto"));
	return (correct);
}

/*
** Checkea los cáracteres de la línea donde se define un color,
** solo puede haber números, espacios y comas
*/

t_bool	check_color_characters(char *line)
{
	int i;

	i = 0;
	while (line[i] == ',' || ft_isdigit(line[i]))
		i++;
	if (line[i])
		return (false);
	return (true);
}

t_bool	check_colors_min_max(int colors[3])
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (colors[i] < 0 || colors[i] > 255)
			return (false);
		i++;
	}
	return (true);
}

t_bool	read_color(char *line, int *color)
{
	int		colors[3];

	while (*line == ' ')
		line++;
	if (!check_color_characters(line))
		return (print_error("Carácter incorrecto en la definición del color"));
	colors[0] = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	colors[1] = ft_atoi(++line);
	while (ft_isdigit(*line))
		line++;
	colors[2] = ft_atoi(++line);
	while (ft_isdigit(*line))
		line++;
	if (!(ft_isdigit(*(line - 1)) && *line == '\0'))
		return (print_error("Carácter de más en la definición de color"));
	if (!check_colors_min_max(colors))
		return (print_error("Valores de color incorrecto"));
	*color = create_trgb(0, colors[0], colors[1], colors[2]);
	return (true);
}
