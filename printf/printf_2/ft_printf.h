/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:00:56 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/06 20:54:34 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef	struct	s_modifiers
{
	char			left_justified;
	char			zero_padded;
	short int		width;
	short int		precision;
}				t_modifiers;

/* FUNCTIONS DECLARATIONS SEPARATED BY FILE */
/* ft_printf.c */
int    		ft_printf(const char *formatString, ...);
char		*format(char *formatString, va_list args, int *characterSum);
/* ft_printf_utils.c */
t_modifiers ft_initialize_struct(void);
int		    is_specifier(char c);
void        get_precision(va_list args, char **format_string, t_modifiers *modifiers);
int		    ft_atoi(const char *str);
int			ft_isdigit(int c);
#endif