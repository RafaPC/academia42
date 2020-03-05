/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:50:25 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/20 11:50:25 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define UPPER_CASE 1
#define LOWER_CASE 2


typedef	struct	s_modifiers
{
	char			left_justified;
	char			zero_padded;
	short int		width;
	short int		precision;
}				t_modifiers;

int    		ft_printf(const char *formatString, ...);
char		*format(char *formatString, va_list args, int *characterSum);
void		printChar(char c, int *characterSum);
void		print_string(char *string, t_modifiers modifiers, int *char_sum);
void		handle_number(int n, t_modifiers modifiers, int *char_sum);
void		print_number(int n, int *characterSum);
void		printHex(long int n, int *characterSum, int letterType);
int			is_specifier(char c);
int			ft_atoi(const char *str);
int			ft_isspace(int c);
void		print_justification(char c, int times);
unsigned int	get_digits(int n);
int			ft_isdigit(int c);
void		format2(char *formatString, t_modifiers modifiers, va_list args, int *characterSum);
unsigned int	ft_strlen(const char *s);
t_modifiers ft_initialize_struct(void);
#endif