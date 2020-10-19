/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:23:17 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/19 20:26:28 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "libft/libft.h"
typedef enum							e_error_type
{missing_argument,
	read_file,
	forbdiden_character}				t_error_type;
typedef	struct	s_error_info
{
	int	t_error_type;
	int error_row;
	int	error_column;

}				t_error_info;
t_bool	check_map(t_error_info *error_info, char *file_path);
int		check_file_path(t_error_info *error_info, char *file_path);
char	**save_file_content(t_error_info *error_info, int fd);
int		print_error(t_error_info *error_info);
#endif
