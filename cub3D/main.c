/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/29 17:21:52 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include "../printf/ft_printf.h"

typedef struct  s_vars {
    void        *mlx;
    void        *win;
	t_data		*img;
	int			x;
	int			y;
}               t_vars;

int				draw_circle(t_vars *vars)
{
	int red = create_trgb(255, 255, 0, 0);
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
			my_mlx_pixel_put(vars->img, vars->x + i, vars->y + j, red);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int             key_hook(int keycode, t_vars *vars)
{	
    ft_printf("Hello %i from key_hook!\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		ft_printf("Window closed");
	}
	else if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
	{
		if (keycode == 119)
			vars->y -= 10;
		else if (keycode == 115)
			vars->y += 10;
		else if (keycode == 97)
			vars->x -= 10;
		else if (keycode == 100)
			vars->x += 10;
		draw_circle(vars);
	}
}
int 		render_frame(int keycode, t_vars *vars)
{
	
}

int		main(int argc, char const *argv[])
{
	t_error_info	*error_info;
	t_bool			save_img;
	t_vars			vars;

	vars.x = 50;
	vars.y = 50;
	vars.img = (t_data*)malloc(sizeof(t_data));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 400, 400, "Hello world");
	vars.img->img = mlx_new_image(vars.mlx, 400, 400);
	vars.img->addr = mlx_get_data_addr(vars.img->img, &vars.img->bits_per_pixel, &vars.img->line_length, &vars.img->endian);
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_frame, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
	save_img = false;
	// if (argc == 3)
	// {
	// 	if (ft_strncmp(argv[1], "--save", 6))
	// 		save_img = true;
	// }
	if (argc > 1)
	{
		char	*file = (char*)argv[1];
		check_map(error_info, file);
	}
	return (0);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}