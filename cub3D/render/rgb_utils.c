/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:24:58 by rprieto-          #+#    #+#             */
/*   Updated: 2020/12/29 17:15:57 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Receives 4 ints with opacity, red, green and blue values (0 to 255)
**	and returns and int with each value taking 2 bytes
*/

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
**	Receives and int with trgb values in it
** and returns the opacity value (0 to 255)
*/

int	get_t(int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}

/*
**	Receives and int with trgb values in it
** and returns the red value (0 to 255)
*/

int	get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}

/*
**	Receives and int with trgb values in it
** and returns the green value (0 to 255)
*/

int	get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}

/*
**	Receives and int with trgb values in it
** and returns the blue value (0 to 255)
*/

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
