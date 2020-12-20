/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:23:17 by rprieto-          #+#    #+#             */
 /*   Updated: 2020/12/11 13:47477 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "libft/libft.h"
# define PI 3.141592
// #define FOV 1.74532
#define FOV 0.785398
/*
**		MINIMAP COLORS
*/
#define WALL_COLOR	16777215
#define SPACE_COLOR 3289650
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

/*
**RAYCASTING
*/

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
	t_data	data;
}				t_texture;

typedef struct	s_sprite
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
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}				t_player_vars;

typedef struct  s_vars
{
	int				ceiling_color;
	int				floor_color;
    t_mlx			mlx;
	t_player_vars	player;
	char			**map;
	t_wall_face		wall_face;
	t_keys			keys_pressed;
	t_texture		textureN;
	t_texture		textureS;
	t_texture		textureE;
	t_texture		textureW;
	t_texture		textureSprite;
	t_list			*sprite;
	int				screen_width;
	int				screen_height;
	float			*distances;
}               t_vars;

typedef enum e_ray_direction
{
	vertical,
	horizontal
}			t_ray_direction;

typedef struct s_coords
{
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
}				t_coords;
/*
**	RAYCASTING
*/
typedef struct		s_ray
{
	float			tang;
	float			x;
	float			y;
	int				tile_step_x;
	int				tile_step_y;
	float			x_intercept;
	float			y_intercept;
	float			x_step;
	float			y_step;
	float			distance_hor;
	float			distance_ver;
	float			angle_beta;
	t_ray_direction	direction;
	char			tile_crossed;
}					t_ray;

/**
**			CHECK FILE THINGS
*/
t_bool		check_arguments(t_bool *save_img, int argc, char **argv);
t_bool		check_file(t_program_params *program_params, const char *file_path);
int			check_file_path(const char *file_path);
t_list		*save_file_content(int fd);
t_bool		check_file_content(t_list *file_content,
t_program_params *t_program_params, t_info_id info_id);
t_bool		check_info_ids(t_bool info_id[8]);
t_info_id	search_identifier(char *line);
t_bool		get_info(t_info_id info_id, char *line,
t_program_params *params);
t_bool		read_resolution(char *line,
t_program_params *program_params);
t_bool		read_path(char *line, char **path_to_texture);
t_bool		read_color(char *line, int *color);
void		initialice_program_params(t_program_params *program_params);
t_bool		read_map(t_list *line, t_program_params *program_params);
/*
**			ERROR HANDLING
*/
t_bool		print_error(const char *msg);
/*
**			RENDER THINGS
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
/*
**			RGB UTILS
*/
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
/*
**			RENDER COLOR
*/
int		add_shade(double distance, int color);
unsigned	get_image_color(t_texture texture, float x, float y);
unsigned	get_wall_color(t_vars *vars, float x, float y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int    get_pixel(t_data image, int x, int y);
/*
**			RENDER SPRITES
*/
void	render_sprites(t_vars *vars);
void	draw_sprite(t_vars *vars, t_sprite sprite);
void	draw_sprite_column(int drawing_position, t_sprite sprite, t_vars *vars);
/*
**			RENDER
*/
int		render_screen(t_vars *vars);
void	display_vars(t_vars *vars);
void	render_column(t_vars *vars, float distance,  float wall_x, int offset_column);
void	draw_sprite(t_vars *vars, t_sprite sprite);
void	render_ceil_and_floor(t_vars *vars, int x_coord, int column_height);
/*
**			DRAW THINGS
*/
void		draw_player(t_vars *vars);
void		draw_map(t_vars *vars);
void		draw_square(t_coords coords, int color, t_data *img);
t_coords	get_coords_struct(int x_start, int y_start, int x_end, int y_end);
/*
**			RAYCASTING
*/
void	main_raycast(t_program_params program_params);
void	raycast(t_vars *vars);
float	get_distance_to_wall(t_vars *vars, float angle, int x_coord,
float *x_wall);
void	set_tile_step(int *tile_step_x, int *tile_step_y, float angle);
float	get_tangent(float angle);
void	check_angle_overflow(float *angle);
float	get_x_intercept_length(t_ray ray, t_player_vars player);
float	get_y_intercept_length(t_ray ray, t_player_vars player);
void	init_ray_values(t_ray *ray, t_player_vars player, float angle);
void	sum_distance(t_ray *ray, t_player_vars player);
void	set_tile_crossed(t_ray *ray, char **map);
void	check_sprite_crossed(t_ray ray, char tile_crossed, t_vars *vars);
/*
**			HOOKS
*/
int		on_key_pressed(int keycode,t_vars *vars);
int		on_key_released(int keycode, t_keys *keys_pressed);
int		on_window_enter(t_vars *vars);
int		on_window_closed(t_vars *vars);
void	check_movement(t_vars *vars);
/*
**			MOVEMENT
*/
void	move(t_player_vars *player, char **map, float angle, float velocity);
void	close_game(t_vars *vars);

/*
**			SPRITE UTILS
*/
void	add_sprite_coords(float x, float y, t_vars *vars);
void    order_sprites(t_list *sprite_list);
/*
**			FREE MEMORY
*/
void	free_textures(t_vars *vars);
void	free_memory(t_vars *vars);
void	free_map(char **map);
#endif
