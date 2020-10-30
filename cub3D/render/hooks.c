/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:44:13 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/30 18:56:03 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>
#include "../../printf/ft_printf.h"

int		on_key_pressed(int keycode,t_vars *vars)
{
	ft_printf("key %i\n", keycode);
	if (keycode == 'w') vars->py -= 10;
	if (keycode == 's') vars->py += 10;
	if (keycode == 'a') vars->px -= 10;
	if (keycode == 'd') vars->px += 10;
	return (0);
}
