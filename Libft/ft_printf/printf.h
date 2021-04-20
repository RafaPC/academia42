/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:44:07 by aiglesia          #+#    #+#             */
/*   Updated: 2021/04/20 16:08:28 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_modifiers
{
	int				fd;
	char			left_justified;
	char			zero_padded;
	int				width;
	int				precision;
}					t_modifiers;

typedef enum e_case_type
{
	lower_case,
	upper_case
}					t_case_type;

char				*read_modifiers(va_list args, char *format_string,
						t_modifiers	*modifiers);
void				format(va_list args, char specifier,
						t_modifiers modifiers, int *char_sum);
t_modifiers			ft_initialize_struct(int fd);
t_bool				is_flag(char c);
int					get_hex_digits(unsigned long n);

/*
**				FT_PRINTF_UTILS.C
*/

char				*get_precision(va_list args, char *format_string,
						t_modifiers *modifiers);
char				*get_width(char *format_string, t_modifiers *modifiers);
int					print_justification(int fd, char c, int times);
t_bool				is_specifier(char c);
/*
**				FT_STRINGS.H
*/

void				handle_string(char *string, t_modifiers modifiers,
						int *char_sum);
void				print_string(char *string, t_modifiers modifiers,
						int *char_sum);
void				print_char(char c, t_modifiers modifiers, int *char_sum);
void				print_symbol(t_modifiers modifiers, int *char_sum);

/*
**				FT_NUMBERS.C
*/

void				handle_number(long n, t_modifiers modifiers, int *char_sum);
void				handle_number_no_prec(long n, t_modifiers modifiers,
						int *char_sum);
void				handle_number_prec_width(long n, t_modifiers modifiers,
						int *char_sum);
void				print_number(int fd, long n, int *char_sum);

/*
**				FT_HEX.C
*/

void				handle_hex_number(unsigned int n, t_modifiers modifiers,
						int *char_sum, char letter_type);
void				print_hex(int fd, unsigned long n, int *char_sum,
						t_case_type case_type);
int					get_hex_digits(unsigned long n);
void				handle_pointer(void *pointer, t_modifiers modifiers,
						int *char_sum);
void				print_pointer(void *pointer, t_modifiers modifiers,
						int *char_sum);

#endif