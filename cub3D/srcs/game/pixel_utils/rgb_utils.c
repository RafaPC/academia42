/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:24:58 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 01:51:38 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Receives 4 ints with opacity, red, green and blue values (0 to 255)
**	and returns and int with each value taking 2 bytes
*/

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
**		Receives and int with trgb values in it
**		and returns the opacity value (0 to 255)
*/

int		get_transparency(int color)
{
	return ((color & (0xFF << 24)) >> 24);
}
