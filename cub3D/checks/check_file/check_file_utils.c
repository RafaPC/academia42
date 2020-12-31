/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:56:47 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/31 12:42:10 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**		Reads the window resolution definition
*/

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
		return (print_error("Invalid character in resolution definition"));
	return (correct);
}

/*
**		Reads a path and checks the extension is .xpm or .XPM
*/

t_bool	read_path(char *line, char **path_to_texture)
{
	t_bool	correct;
	int		path_length;

	correct = true;
	while (*line == ' ')
		line++;
	path_length = ft_strlen(line);
	if (!(*path_to_texture = (char*)malloc(sizeof(char) * (path_length + 1))))
		return (print_error("Error while allocating memory"));
	ft_strlcpy(*path_to_texture, line, path_length + 1);
	if (ft_strncmp("XPM", &(*path_to_texture)[path_length - 3], 3)
	&& ft_strncmp("xpm", &(*path_to_texture)[path_length - 3], 3))
		return (print_error("Wrong extension of file"));
	return (correct);
}

/*
**		Checks there are only numbers and commas
*/

t_bool	check_color_characters(char *line)
{
	int commas;

	commas = 0;
	while (*line == ',' || ft_isdigit(*line))
	{
		if (*line == ',')
			commas++;
		line++;
	}
	if (*line || commas > 2)
		return (false);
	return (true);
}

/*
**		Reads a color definition
*/

t_bool	read_color(char *line, int *color)
{
	int		colors[3];

	while (*line == ' ')
		line++;
	if (!check_color_characters(line))
		return (print_error("Invalid character in color definition"));
	colors[0] = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	colors[1] = ft_atoi(++line);
	while (ft_isdigit(*line))
		line++;
	colors[2] = ft_atoi(++line);
	while (ft_isdigit(*line))
		line++;
	if (colors[0] > 255 || colors[1] > 255 || colors[2] > 255)
		return (print_error("Incorrect rgb values, max should be 255"));
	*color = create_trgb(0, colors[0], colors[1], colors[2]);
	return (true);
}
