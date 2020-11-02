/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:58:14 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/02 13:49:37 by rprieto-         ###   ########.fr       */
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


// void	drawRays3D(t_vars *vars)
// {
// 	int r, mx, my, mp, dof;
// 	float rx, ry, ra, xo, yo;

// 	ra = vars->pangle;
// 	for (r = 0; r < 1; r++)
// 	{
// 		dof = 0;
// 		float aTan = -1/tan(ra);
// 		if (ra > PI)
// 		{
// 			ry = (((int)vars->py>>6)<<6) - 0.0001;
// 			rx = (vars->py - ry) * aTan + vars->px;
// 			yo = -64;
// 			xo = -yo * aTan;
// 		}
// 		else if (ra < PI)
// 		{
// 			ry = (((int)vars->py>>6)<<6) + 64;
// 			rx = (vars->py - ry) * aTan + vars->px;
// 			yo = 64;
// 			xo = -yo * aTan;
// 		}
// 		else if (ra == 0 || ra == PI)
// 		{
// 			rx = vars->px;
// 			ry = vars->py;
// 			dof = 8;
// 		}

// 	}
// }
}