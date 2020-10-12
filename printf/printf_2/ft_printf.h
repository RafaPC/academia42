/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:00:56 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/12 15:54:53 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
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
void		print_string(char *string, t_modifiers modifiers, int *char_sum);
void		handle_string(char *string, t_modifiers modifiers, int *char_sum);
char		*modifiers_to_string(t_modifiers modifiers);
void		print_char(char c, t_modifiers modifiers, int *char_sum);
void		handle_integer(int n, t_modifiers modifiers, int *char_sum);
/* ft_printf_utils.c */
t_modifiers 	ft_initialize_struct(void);
int		    	is_specifier(char c);
char        	*get_precision(va_list args, char *format_string, t_modifiers *modifiers);
char			*get_width(char *format_string, t_modifiers *modifiers);
int		    	ft_atoi(const char *str);
char			*ft_strjoin_and_free(char const *s1, char const *s2);
void			print_justification(char c, int times);
int				get_greater(int n1, int n2);
// unsigned int	get_digits(int n);
/* ft_numbers.c */
void	handle_number(long int n, t_modifiers modifiers, int *char_sum);
void	print_number2(long int n, t_modifiers modifiers, int *char_sum);
void	print_number(long n, int *char_sum);
#endif