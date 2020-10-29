/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:16:04 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/29 12:24:20 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../../printf/ft_printf.h"

int		create_trgb(int t, int r, int g, int b)
{
	
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}

int		get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}

int		get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int		add_shade(double distance, int color)
{
	int r, g, b;
	static int print = 1;
	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	if (print)
		ft_printf("Color (before change):\nRed:%i\nGreen:%i\nBlue:%i\n", r, g, b);
	r = r - (r * distance);
	g = g - (g * distance);
	b = b - (b * distance);
	if (print)
		ft_printf("Color (after change):\nRed:%i\nGreen:%i\nBlue:%i\n", r, g, b);
	print = 0;
	return (create_trgb(get_t(color), r, g, b));
}
