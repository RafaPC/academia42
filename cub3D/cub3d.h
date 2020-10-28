/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:23:17 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/28 18:07:23 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "libft/libft.h"
typedef enum	e_error_type
{	
	missing_argument_error,
	open_file_error,
	read_file_error,
	forbdiden_character_error,
	duplicated_info_error
}				t_error_type;
	
typedef enum	e_info_id
{	
	id_resolution,
	id_path_north,
	id_path_south,
	id_path_west,
	id_path_east,
	id_path_sprite,
	id_color_floor,
	id_color_ceilling
}				t_info_id;
typedef	struct	s_error_info
{
	enum e_error_type	error_type;
	int 				error_row;
	int					error_column;
}				t_error_info;

typedef struct	s_line
{
	char			*line;
	struct s_line	*next_line;
}				t_line;
typedef struct	s_program_params
{
	int			resolution_x;
	int			resolution_y;
	char		*path_NO_texture;
	char		*path_SO_texture;
	char		*path_WE_texture;
	char		*path_EA_texture;
	char		*path_sprite_texture;
	int			*floor_color;
	int			*ceilling_color;
}				t_program_params;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

t_bool		check_map(t_error_info *error_info, char *file_path);
int			check_file_path(t_error_info *error_info, char *file_path);
t_line		*save_file_content(t_error_info *error_info, t_line *file_content, int fd);
t_bool		print_error(t_error_info *error_info);
t_bool		check_file_content(t_error_info *error_info, t_line *file_content,
t_program_params *t_program_params);
t_bool		check_info_ids(t_bool info_id[8]);
t_info_id	search_identifier(char *line);
t_bool		get_info(t_info_id info_id, t_error_info *error_info, char *line,
t_program_params *params);
t_bool		read_resolution(t_error_info *error_info, char *line,
t_program_params *program_params);
t_bool		read_path(t_error_info *error_info, char *line, char **path_to_texture);
t_bool		read_color(t_error_info *error_info, char *line, int *color);
void		initialice_program_params(t_program_params *program_params);
#endif
