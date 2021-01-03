/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:23:17 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 21:11:55 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# define PI 3.141592

/*
**		 FIELD OF VIEW
*/
# define FOV 0.785398

/*
**	DISPLAY TEXT COLOR
*/
# define TEXT_COLOR 4294967295

/*
**	KEYBOARD DEFINES
*/

# define ESC_KEY			65307
# define ARROW_UP_KEY		65362
# define ARROW_LEFT_KEY		65361
# define ARROW_RIGHT_KEY	65363
# define ARROW_DOWN_KEY		65364
# define LEFT_CTRL_KEY		65507

/*
**		FILE READING ENUM
*/

typedef enum	e_info_id
{
	id_resolution = 1,
	id_path_north,
	id_path_south,
	id_path_west,
	id_path_east,
	id_path_sprite,
	id_path_sprite_2,
	id_path_sprite_3,
	id_color_floor,
	id_color_ceilling
}				t_info_id;

/*
**		CUB PARAMETERS STRUCT
*/
typedef struct	s_program_params
{
	int			window_width;
	int			window_height;
	char		*path_north_texture;
	char		*path_south_texture;
	char		*path_west_texture;
	char		*path_east_texture;
	char		*path_sprite_texture;
	char		*path_sprite2_texture;
	char		*path_sprite3_texture;
	int			floor_color;
	int			ceilling_color;
	int			player_x;
	int			player_y;
	float		player_angle;
	char		**map;
}				t_program_params;

/*
**		IMAGE DATA
*/
typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

/*
**		STRUCT TO GROUP THE KEYS
*/
typedef struct	s_keys
{
	t_bool		w;
	t_bool		a;
	t_bool		s;
	t_bool		d;
	t_bool		left_arrow;
	t_bool		right_arrow;
	t_bool		up_arrow;
	t_bool		down_arrow;
	t_bool		left_ctrl;
}				t_keys;

typedef enum	e_wall_face
{
	north_face,
	south_face,
	east_face,
	west_face
}				t_wall_face;

/*
**		TEXTURE INFO STRUCT
*/
typedef struct	s_texture
{
	int		width;
	int		height;
	t_data	data;
}				t_texture;

/*
**		SPRITE INFO STRUCT
*/
typedef struct	s_sprite
{
	float			x;
	float			y;
	float			distance;
	int				size_half;
	int				center_x;
	int				center_y;
	t_texture		texture;
}				t_sprite;

/*
**		MLX VARIABLES STRUCT
*/
typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_data		*img;
}				t_mlx;

/*
**		PLAYER INFORMATION STRUCT
*/
typedef struct	s_player_vars
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}				t_player_vars;

/*
**		STRUCT TO GROUP TEXTURES
*/
typedef struct	s_textures
{
	t_texture		wall_north;
	t_texture		wall_south;
	t_texture		wall_east;
	t_texture		wall_west;
	t_texture		sprite_1;
	t_texture		sprite_2;
	t_texture		sprite_3;
}				t_textures;

/*
**		MAIN STRUCTURE
*/

typedef struct	s_vars
{
	t_mlx			mlx;
	char			**map;
	t_textures		textures;
	int				ceiling_color;
	int				floor_color;
	t_player_vars	player;
	t_wall_face		wall_face;
	t_keys			keys_pressed;
	t_list			*sprite;
	int				window_width;
	int				window_height;
	float			*distances;
	int				max_col_height;
	int				mouse_x;
	int				mouse_y;
	int				y_offset;
	int				score;
}				t_vars;

/*
**	STRUCT USED FOR DRAWING
*/
typedef struct	s_coords
{
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
}				t_coords;

/*
**		RAYCASTING
*/
typedef enum	e_ray_direction
{
	vertical,
	horizontal
}				t_ray_direction;

typedef struct	s_ray
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
}				t_ray;

/*
**			-------------------------------------------------
**						FUNCTIONS PROTOTYPES
**			-------------------------------------------------
**
**
**				MAIN
*/
t_bool			check_arguments(t_bool *save_img, int argc, char **argv);
/*
**			-------------------------------------------------
**						FILE READING FUNCTIONS
**			-------------------------------------------------
**				CHECK FILE
*/
t_bool			get_cub_data(t_program_params *program_params,
const char *file_path);
t_bool			save_file_lines(t_list **file_content, const char *file_path);
t_bool			read_file_lines(t_list *file_content,
t_program_params *program_params, t_info_id info_id, t_bool list_info_ids[10]);
t_bool			get_info(t_info_id info_id, char *line,
t_program_params *params);
t_info_id		search_identifier(char *line);
/*
**				READ INFO
*/
t_bool			read_resolution(char *line, t_program_params *program_params);
t_bool			read_path(char *line, char **path_to_texture);
t_bool			read_color(char *line, int *color);
t_bool			check_color_characters(char *line);
/*
**				FILE READING UTILS
*/
void			initialice_program_params(t_program_params *program_params);
void			initialice_info_ids(t_bool info_id[10]);
t_bool			check_info_ids(t_bool info_id[10]);
/*
**				ERROR MESSAGES
*/
t_bool			print_error(const char *msg);
t_bool			print_error_line(const char *msg, char *line);
t_bool			print_error_map(const char *msg, int row, int col);
t_bool			print_error_texture(const char *file);
/*
**				READ MAP
*/
t_bool			read_map(t_list *line, t_program_params *program_params);
t_bool			check_map_characters(char **map, int y, int x,
t_program_params *params);
t_bool			map_is_closed(char **map, int y, int x);
t_bool			set_player_parameters(char angle_char, int y, int x,
t_program_params *params);
int				get_map_height(t_list *line);
/*
**			------------------------------------------------
**							GAME FUNCTIONS
**			------------------------------------------------
**				START GAME
*/
void			start_game(t_program_params program_params, t_bool save_img);
void			set_hooks(t_vars *vars);
void			set_window_size(t_vars *vars, int window_width,
int window_height);
/*
**				INITIALICE GAME VARIABLES
*/
void			init_to_null(t_vars *vars);
t_bool			init_game_variables(t_vars *vars, t_program_params params);
void			init_game_variables2(t_vars *vars, t_program_params params);
t_bool			init_textures(void *mlx, t_textures
*textures, t_program_params params);
t_bool			init_texture(void *mlx, t_texture *text, char *file);
/*
**				RGB UTILS
*/
int				create_trgb(int t, int r, int g, int b);
int				get_transparency(int color);
int				add_shade(float distance, int color);
/*
**				DRAWING UTILS
*/
void			draw_square(t_coords coords, int color, t_data *img);
t_coords		get_coords_struct(int x_start, int y_start, int x_end,
int y_end);
/*
**				PIXEL UTILS
*/
void			put_pixel(t_data *data, int x, int y, int color);
int				get_pixel(t_data image, int x, int y);
/*
**				TEXTURE UTILS
*/
int				get_wall_color(t_textures textures, t_wall_face wall_face,
float x, float y);
int				get_image_color(t_texture texture, float x, float y);
/*
**				RENDER SPRITES
*/
void			render_sprites(t_vars *vars);
void			draw_sprite(t_vars vars, t_sprite sprite);
void			draw_sprite_column(t_vars vars, t_sprite sprite,
int drawing_position);
/*
**				RENDER
*/
void			render_once(t_vars *vars);
int				render_screen(t_vars *vars);
void			render_column(t_vars *vars, float distance, float wall_x,
int window_x);
void			render_ceil_and_floor(t_vars *vars, int x_coord);
void			display_score(t_vars vars);
/*
**				RAYCASTING
*/
void			raycast(t_vars *vars);
float			get_distance_to_wall(t_vars *vars, float angle, int x_window,
float *x_wall);
void			init_ray_values(t_ray *ray, t_player_vars player, float angle);
void			init_ray_values2(t_ray *ray, float angle);
void			sum_distance(t_ray *ray, t_player_vars player);
/*
**				RAYCASTING UTILS
*/
float			get_x_intercept_length(t_ray ray, t_player_vars player);
float			get_y_intercept_length(t_ray ray, t_player_vars player);
void			check_angle_overflow(float *angle);
void			set_tile_crossed(t_ray *ray, char **map);
void			check_sprite_crossed(t_ray ray, char tile_crossed,
t_vars *vars);
/*
**				HOOKS
*/
int				on_key_pressed(int keycode, t_vars *vars);
int				on_key_released(int keycode, t_vars *vars);
int				on_window_focused(t_vars *vars);
int				on_window_closed(t_vars *vars);
/*
**				MOVEMENT
*/
void			check_movement(t_vars *vars, t_keys keys);
void			move(t_player_vars *player, char **map, float angle,
float velocity);
void			check_mouse_move(t_vars *vars, t_bool left_ctrl_key);
t_bool			is_moving(t_keys keys, t_vars vars);
t_bool			blocks_movement(char c);

/*
**				SPRITE UTILS
*/
void			add_sprite_coords(float x, float y, t_vars *vars,
t_texture texture);
void			order_sprites(t_list *sprite_list);
void			calculate_sprite_info(t_sprite *sprite, t_player_vars player,
t_vars vars);
/*
**				FREE MEMORY
*/
void			free_and_close(t_vars *vars);
void			free_textures(void *mlx, t_textures textures);
void			free_map(char **map);
void			free_program_params(t_program_params params);
/*
**				SCREENSHOT
*/
void			take_screenshot(t_vars vars);
void			save_image(t_data render, t_vars vars);
#endif
