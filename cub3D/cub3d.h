/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:23:17 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/06 18:55:46 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "libft/libft.h"
# define PI 3.141592
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
}			t_line;
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

typedef struct s_keys
{
	t_bool		w;
	t_bool		a;
	t_bool		s;
	t_bool		d;
}				t_keys;
//RAYCASTING
typedef enum	e_wall_face
{
	north_face,
	south_face,
	east_face,
	west_face
}				t_wall_face;
typedef struct	s_texture
{
	int		width;
	int		height;
	void	*data;
}				t_texture;

typedef struct  s_vars {
    void        	*mlx;
    void        	*win;
	t_data			*img;
	float			px, py;
	float			pdx, pdy, pangle;
	int				map[8][8];
	t_wall_face		wall_face;
	t_keys			keys_pressed;
	t_texture		texture;
}               t_vars;

typedef enum	e_compare_flag
{	
	less_than,
	greater_than
}				t_compare_flag;

/*
**	RAYCASTING
*/
typedef struct	s_ray
{
	float		tang;
	float		x;
	float		y;
	int			tile_step_x;
	int			tile_step_y;
	float		x_intercept;
	float		y_intercept;
	float		x_step;
	float		y_step;
}				t_ray;




/**
**			CHECK FILE THINGS
*/
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
/*
**			RENDER THINGS
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
/*
**			RENDER COLOR
*/
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		add_shade(double distance, int color);
/*
**			RENDER
*/
int		render_screen(t_vars *vars);
void	display_player(t_vars *vars);
void	draw_map(t_vars *vars);
void	draw_square(int width, int height, int xpos, int ypos, int color, t_vars *vars);
void	draw_line(t_vars *vars, float xend, float yend, int color);
void	draw_fov(t_vars *vars, int color);
void	display_vars(t_vars *vars);
void	render_column(t_vars *vars, float distance);
/*
**			RAYCASTING
*/
void	raycast(t_vars *vars);
float	drawRays3D(t_vars *vars, float angle);
void	set_tile_step(int *tile_step_x, int *tile_step_y, float angle);
float	get_tangent(float angle);
void	check_angle_overflow(float *angle);
float	get_x_intercept_length(t_ray ray, t_vars vars);
float	get_y_intercept_length(t_ray ray, t_vars vars);
t_ray	init_ray_values(t_vars vars, float angle);
/*
**			HOOKS
*/
int		on_key_pressed(int keycode,t_vars *vars);
void	check_movement(t_vars *vars);
int		on_key_released(int keycode, t_vars *vars);
#endif
