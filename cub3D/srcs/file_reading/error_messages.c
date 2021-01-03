/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 17:21:59 by rprieto-          #+#    #+#             */
/*   Updated: 2021/01/03 21:10:05 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
**		Receives a string and prints it with "Error\n" before it
*/

t_bool	print_error(const char *msg)
{
	ft_printf("Error\n%s\n", msg);
	return (false);
}

/*
**		Prints an error message and a line
*/

t_bool	print_error_line(const char *msg, char *line)
{
	print_error(msg);
	ft_printf("In line %s\n", line);
	return (false);
}

/*
**		Prints an error message and the row and col within the map
*/

t_bool	print_error_map(const char *msg, int row, int col)
{
	print_error(msg);
	ft_printf("In the map row %i and col %i\n", row + 1, col + 1);
	return (false);
}

/*
**		Prints a texture error message and the texture that failed
*/

t_bool	print_error_texture(const char *file)
{
	print_error("Failed to initialice a texture");
	ft_printf("Texture that failed: %s\n", file);
	return (false);
}
