#ifndef CONVERT_HPP
# define CONVERT_HPP
#include <string>

typedef	enum	floating_point_type_e
{
	float_type = 1,
	double_type
}				floating_point_type_t;

void	display_from_char(char c);
void	display_from_integer(int number);
void	display_from_float(float number);
void	display_from_double(double number);
void	display_from_special_case(std::string arg);
//		IS TYPE
bool	is_special_case(std::string argument);
bool	is_integer(std::string arg);
int		is_point_value(std::string arg);
//		UTILS
void	print_char(char character);
bool	has_decimal_value(double number);
#endif