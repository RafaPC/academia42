/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:17:17 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/10 17:42:53 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

//TODO: mirar si junto funcionas de checkear carácteres del mapa
//también mirar el ir pasando líneas vacías al acabar de leer todos los parámetros
//para no leer líneas vacías en el mapa

t_bool		check_map_characters(t_list *line_elem)
{
	char	*line;
	t_bool	player_pos;

	player_pos = false;
	while (line_elem)
	{
		line = line_elem->content;
		while (*line)
		{
			if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			{
				if (player_pos)
					return (false);
				player_pos = true;
			}
			else if (*line != '0' && *line != '1' && *line != '2' && *line != ' ')
				return (false);
			line++;
		}
		line_elem = line_elem->next;
	}
	if (!player_pos) //No se ha encontrado con N, S, E o W
		return (false);
	return (true);
}

int			get_map_height(t_list *line)
{
	int i;

	i = 0;
	while (line)
	{
		i++;
		line = line->next;
	}
	return (i);
}

static void	set_player_angle(char c, float *angle)
{
	if (c == 'N')
		*angle = PI/2;
	else if (c == 'S')
		*angle = (3*PI)/2;
	else if (c == 'E')
		*angle = 0;
	else
		*angle = PI;
}

static void	set_player_parameters(char **map, t_program_params *program_params)
{
	int x;
	int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || 
			map[y][x] == 'E' || map[y][x] == 'W')
			{
				program_params->player_y = y;
				program_params->player_x = x;
				set_player_angle(map[y][x], &program_params->player_angle);
				map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	save_map(t_list *line_elem, char **map)
{
	while (line_elem)
	{
		*map = ft_strdup(line_elem->content);
		(map)++;
		line_elem = line_elem->next;
	}
	*map = NULL;
}

static t_bool		map_is_closed(char **map)
{
	int y;
	int x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (y == 0 || map[y + 1] == NULL ||
				x == 0 || map[y][x + 1] == '\0')
					return (false);
				else if (map[y-1][x] == ' ' || map[y+1][x] == ' ' ||
				map[y][x-1] == ' ' || map[y][x+1] == ' ')
					return (false);
			}
			x++;	
		}
		y++;
	}
	return (true);
}

t_bool		read_map(t_error_info *error_info, t_list *line, t_program_params *program_params)
{
	program_params->map = (char**)malloc((get_map_height(line) + 1) * sizeof(char*));
	save_map(line, program_params->map);
	if (!check_map_characters(line))
		return (raise_error(error_info, wrong_map_character));
	if (!map_is_closed(program_params->map)) //TODO: pasarle error_info y que guarde fila y columna
		return (raise_error(error_info, map_not_closed_error));
	set_player_parameters(program_params->map, program_params);
	return (true);
}
