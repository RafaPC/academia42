/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:56:47 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/22 15:40:13 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_bool check_resolution(t_error_info error_info, char *line, t_program_params *program_params)
{
	int i;
	t_bool correct;
	i = 0;
	if (line++ != 'R')
		correct = false;
	while(ft_isspace(*line))
		line++;
	program_params->resolution_x = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
	while(ft_isspace(*line))
		line++;
	program_params->resolution_y = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
}
