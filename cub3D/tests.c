/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:58:14 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/29 12:58:38 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	 tests(void *img)
{
	//PRUEBAS
	int white = create_trgb(0, 255, 255, 255);
	int color = create_trgb(0, 200, 100, 50);
	//CUADRADO
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
			my_mlx_pixel_put(&img, 1 + i, 1 + j, white);
	}
	//CUADRADO OSCURO
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
			my_mlx_pixel_put(&img, 1 + i, 50 + j, add_shade(0, color));
	}
	//RECTAS SECANTES
	for (int i = 0; i < 50; i++)
	{
		my_mlx_pixel_put(&img, 50 + i, 50 + i, 0x00FF0000);
		my_mlx_pixel_put(&img, 100 - i, 50 + i, 0x00FF0000);
	}
	//TRIANGULO RECTANGULO
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < i; j++)
			my_mlx_pixel_put(&img, 120 + j, 120 + i, 0x0000FFFF);
	}
	//TRIANGULO NORMAL
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < i; j++)
			my_mlx_pixel_put(&img, 195 -i + (j * 2), 170 + i, 0x0000FFFF);
	}

	//ROMBO
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < i; j++)
			my_mlx_pixel_put(&img, 195 - i + (j * 2), 0 + i, 0x0000FFFF);
		for (int j = 0; j < i; j++)
			my_mlx_pixel_put(&img, 195 - i + (j * 2), 99 - i, 0x0000FFFF);
	}

	//CUADRADO GRADIENTE
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
			my_mlx_pixel_put(&img, 200 + j, 230 + i, create_trgb(255, 150, 60 + i * 2, j * 4));
	}

	//CUADRADO GRADIENTE
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
			my_mlx_pixel_put(&img, j, 200 + i, create_trgb(255, 150, 60 + i * 2, 20));
	}
}