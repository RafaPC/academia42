/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:36:35 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/19 21:30:01 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

t_bool	check_map(t_error_info *error_info, char *file_path)
{
	char	**file_content;
	int 	fd;

	if ((fd = check_file_path(error_info, file_path)) < 0)
		return (print_error(error_info));
	if (!(file_content = save_file_content(error_info, fd)))
		return (print_error(error_info));
	return (true);
}

int		check_file_path(t_error_info *error_info, char *file_path)
{
	int	fd;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		error_info->t_error_type = read_file;
	return (fd);
}

char	**save_file_content(t_error_info *error_info, int fd)
{
	char	**map;
	char	*line;
	int		i;
	int result;

	i = 0;
	map = NULL;
	while(get_next_line(fd, &line) == 1)
		map[i++] = line;
	map[i] = NULL;
	return (map);
}

int		print_error(t_error_info *error_info)
{

}
