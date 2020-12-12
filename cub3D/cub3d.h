/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:23:17 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/11 13:47:27 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "libft/libft.h"
# define PI 3.141592
// #define FOV 1.74532
#define FOV 0.785398
typedef enum	e_error_type
{	
	missing_argument_error = 1,
	too_many_args_error,
	second_arg_error,
	wrong_filename_error,
	wrong_extension_error,
	open_file_error,
	read_file_error,
	forbdiden_character_error,
	duplicated_info_error,
	wrong_identifier_error,
	color_wrong_character,
	color_wrong_value,
	missing_information_error,
	wrong_map_character,
	map_not_closed_error
}				t_error_type;
	
typedef enum	e_info_id
{	
	id_resolution = 1,
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
	int			floor_color;
	int			ceilling_color;
	int			player_x;
	int			player_y;
	float		player_angle;
	char		**map;
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
	t_bool		left_arrow;
	t_bool		right_arrow;
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
	t_data	*data;
}				t_texture;

typedef struct s_sprite
{
	float			x;
	float			y;
	float			angle;
	float			distance;
	int				size_half;
	int				center_x;
	int				center_y;
	struct s_sprite *next_sprite;
}				t_sprite;

typedef struct	s_mlx {
	void        	*mlx;
    void        	*win;
	t_data			*img;
}				t_mlx;
typedef struct	s_player_vars {
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pangle;
}				t_player_vars;
typedef struct  s_vars {
    t_mlx			mlx;
	t_player_vars	player_vars;
	char			**map;
	t_wall_face		wall_face;
	t_keys			keys_pressed;
	t_texture		*textureN;
	t_texture		*textureS;
	t_texture		*textureE;
	t_texture		*textureW;
	t_texture		*textureSprite;
	float			texture_x;
	t_list			*sprite;
	int				screen_width;
	int				screen_height;
	float			*distances;
}               t_vars;

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
t_bool		check_arguments(t_error_info *error_info, t_bool *save_img, int argc, char **argv);
t_bool		check_file(t_error_info *error_info, t_program_params *program_params, const char *file_path);
int			check_file_path(t_error_info *error_info, const char *file_path);
t_list		*save_file_content(t_error_info *error_info, int fd);
t_bool		check_file_content(t_error_info *error_info, t_list *file_content,
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
t_bool		read_map(t_error_info *error_info, t_list *line, t_program_params *program_params);
/*
**			ERROR HANDLING
*/
void		init_error_struct(t_error_info *error_info);
t_bool		print_error(t_error_info *error_info);
t_bool		raise_error(t_error_info *error_info, t_error_type error_id);

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
unsigned	get_image_color(t_texture texture, float x, float y);
unsigned	get_wall_color(t_vars *vars, float x, float y);
/*
**			RENDER
*/
void	render_sprites(t_vars *vars);
int		render_screen(t_vars *vars);
void	display_player(t_vars *vars);
void	draw_map(t_vars *vars);
void	draw_square(int width, int height, int xpos, int ypos, int color, t_vars *vars);
void	draw_line(t_vars *vars, float xend, float yend, int color);
void	draw_fov(t_vars *vars, int color);
void	display_vars(t_vars *vars);
void	render_column(t_vars *vars, float distance);
unsigned int    get_pixel(t_data *image, int x, int y);
void	draw_sprite(t_vars *vars, t_sprite sprite);
/*
**			RAYCASTING
*/
void	main_raycast(t_program_params program_params);
void	raycast(t_vars *vars);
float	drawRays3D(t_vars *vars, float angle);
void	set_tile_step(int *tile_step_x, int *tile_step_y, float angle);
float	get_tangent(float angle);
void	check_angle_overflow(float *angle);
float	get_x_intercept_length(t_ray ray, t_vars vars);
float	get_y_intercept_length(t_ray ray, t_vars vars);
t_ray	init_ray_values(t_player_vars vars, float angle);
/*
**			HOOKS
*/
int		on_key_pressed(int keycode,t_keys *keys_pressed);
void	check_movement(t_vars *vars);
int		on_key_released(int keycode, t_keys *keys_pressed);
void	move_left(t_vars *vars);

/*
**			SPRITE UTILS
*/
void	add_sprite_coords(float x, float y, t_vars *vars);
void    order_sprites(t_list *sprite_list);
void	move_right(t_vars *vars);
#endif
