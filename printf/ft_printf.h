/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:00:56 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/15 13:48:32 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
#include "libft/libft.h"
typedef enum				e_case_type
{lower_case, upper_case}	t_case_type;
typedef	struct	s_modifiers
{
	char			left_justified;
	char			zero_padded;
	int				width;
	int				precision;
}				t_modifiers;
/*
**				FUNCTIONS DECLARATIONS SEPARATED BY FILE
**
**				FT_PRINTF.C
*/
int				ft_printf(const char *format_string, ...);
char			*read_modifiers(va_list args, char *format_string,
t_modifiers	*modifiers, int *char_sum);
void			format(va_list args, char specifier,
t_modifiers modifiers, int *char_sum);
t_modifiers		ft_initialize_struct(void);
t_bool			is_specifier(char c);
/*
**				FT_PRINTF_UTILS.C
*/
char			*get_precision(va_list args, char *format_string,
t_modifiers *modifiers);
char			*get_width(char *format_string, t_modifiers *modifiers);
int				print_justification(char c, int times);
unsigned		get_digits(int n);
/*
**				FT_STRINGS.H
*/
void			handle_string(char *string, t_modifiers modifiers,
int *char_sum);
void			print_string(char *string, t_modifiers modifiers,
int *char_sum);
void			print_char(char c, t_modifiers modifiers, int *char_sum);
void			print_symbol(t_modifiers modifiers, int *char_sum);
/*
**				FT_NUMBERS.C
*/
void			handle_number(long n, t_modifiers modifiers, int *char_sum);
void			handle_number1_5(long n, t_modifiers modifiers, int *char_sum);
void			handle_number2(long n, t_modifiers modifiers, int *char_sum);
void			print_number(long n, int *char_sum);
void			handle_decimal(long n, t_modifiers modifiers, int *char_sum);

/*
**				FT_HEX.C
*/
void			handle_hex_number(long n, t_modifiers modifiers,
int *char_sum, char letter_type);
void			handle_hex_number2(long n, t_modifiers modifiers,
int *char_sum, char letter_type, int justification_width);
void			print_hex(long n, int *char_sum, t_case_type letter_type);
int				get_hex_digits(long n);
void			handle_pointer(void *pointer, t_modifiers modifiers,
int *char_sum);
void			print_pointer(void *pointer, t_modifiers modifiers,
int *char_sum);
#endif
