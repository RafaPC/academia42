/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:00:56 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/13 11:41:39 by rprieto-         ###   ########.fr       */
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
#define ABS(n) (n < 0) ? -n : n

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
char		*read_modifiers( va_list args, char *formatString, t_modifiers *modifiers, int *characterSum);
void		format2(va_list args, char specifier, t_modifiers modifiers, int *char_sum);
/* ft_printf_utils.c */
t_modifiers 	ft_initialize_struct(void);
int		    	is_specifier(char c);
char        	*get_precision(va_list args, char *format_string, t_modifiers *modifiers);
char			*get_width(char *format_string, t_modifiers *modifiers);
int		    	ft_atoi(const char *str);
char			*ft_strjoin_and_free(char const *s1, char const *s2);
int				print_justification(char c, int times);
int				get_greater(int n1, int n2);
/* ft_strings.c */
void	handle_string(char *string, t_modifiers modifiers, int *char_sum);
void	print_string(char *string, t_modifiers modifiers, int *char_sum);
void	print_char(char c, t_modifiers modifiers, int *char_sum);
void	print_symbol(t_modifiers modifiers, int *char_sum);
/* ft_numbers.c */
void	handle_number(long int n, t_modifiers modifiers, int *char_sum);
void	handle_number2(long int n, t_modifiers modifiers, int *char_sum);
void	print_number(long n, int *char_sum);

/* ft_hex.c */
void		handle_hex_number(long n, t_modifiers modifiers, int *char_sum, char letter_type);
void		handle_hex_number2(long n, t_modifiers modifiers, int *char_sum, char letter_type, int justification_width);
void		print_hex(long n, int *char_sum, char letter_type);
int			get_hex_digits(long n);
void		handle_pointer(void *pointer, t_modifiers modifiers, int *char_sum);
void		print_pointer(void *pointer, int *char_sum);
#endif