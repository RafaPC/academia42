/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:00:56 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/07 21:11:26 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
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
char		*format( va_list args, char *formatString, int *characterSum);
void	format2(va_list args, char specifier, t_modifiers modifiers, int *char_sum);
void	print_string(char *string, t_modifiers modifiers, int *char_sum);
void	handle_string(char *string, t_modifiers modifiers, int *char_sum);
char	*modifiers_to_string(t_modifiers modifiers);
/* ft_printf_utils.c */
t_modifiers ft_initialize_struct(void);
int		    is_specifier(char c);
void        get_precision(va_list args, char **format_string, t_modifiers *modifiers);
int		    ft_atoi(const char *str);
char		*ft_strjoin_and_free(char const *s1, char const *s2);
void	print_justification(char c, int times);
#endif