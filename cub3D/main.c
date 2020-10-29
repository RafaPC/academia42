/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:39:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/29 13:34:48 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
	t_data		*img;
}               t_vars;

int             key_hook(int keycode, t_vars *vars)
{
	static int offset = 0;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
			my_mlx_pixel_put(vars->img, offset + i, offset + j, create_trgb(255, 255, 0, 0));
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	offset += 41;
    printf("Hello from key_hook!\n");
}

int		main(int argc, char const *argv[])
{
	t_error_info	*error_info;
	t_bool			save_img;
	t_vars			vars;
	t_data img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 400, 400, "Hello world");
	vars.img->img = mlx_new_image(vars.mlx, 400, 400);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
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