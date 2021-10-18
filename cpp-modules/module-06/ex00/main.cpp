#include <string>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <float.h>
#include "convert.hpp"

int main(int argc, char const *argv[])
{
	if (argc != 2)
		return (0);

	int			point_value_type;
	std::string	argument = argv[1];

	if (is_special_case(argument))
		display_from_special_case(argument);
	else if (argument.length() == 1 && !isdigit(argument[0]))
		display_from_char(argument[0]);
	else if (is_integer(argument))
		display_from_integer(atoi(argument.c_str()));
	else if ((point_value_type = is_point_value(argument)))
	{
		if (point_value_type == float_type)
			display_from_float(strtof(argument.c_str(), NULL));
		else
			display_from_double(strtod(argument.c_str(), NULL));
	}
	else
		std::cout << "Error: Invalid input\n";
	return (0);
}

void	display_from_char(char character)
{
	std::cout << "char: '" << character << "'\nint: " << static_cast<int>(character) << "\nfloat: "
	"" << static_cast<float>(character) << "\ndouble: " << static_cast<double>(character) << '\n';
}

void	display_from_integer(int number)
{
	print_char(static_cast<char>(number));
	std::cout << "int: " << number << '\n';
	if (number >= 1000000)
		std::cout << "float: " << static_cast<float>(number) << "f\n"
		"double: " << static_cast<double>(number) << '\n';
	else
		std::cout << "float: " << static_cast<float>(number) << ".0f\n"
		"double: " << static_cast<double>(number) << ".0\n";
}

void	display_from_float(float number)
{
	print_char(static_cast<char>(number));
	if (number > INT_MAX || number < INT_MIN)
		std::cout << "int: impossible\n";
	else
		std::cout << "int: " << static_cast<int>(number) << '\n';
	if (has_decimal_value(number) || number >= 1000000) // if number is greater than 100000 will be displayed in scientific notation
		std::cout << "float: " << number << "f\n"
		"double: " << static_cast<double>(number) << '\n';
	else
		std::cout << "float: " << number << ".0f\n"
		"double: " << static_cast<double>(number) << ".0\n";
}

void	display_from_double(double number)
{
	print_char(static_cast<char>(number));
	if (number > INT_MAX || number < INT_MIN)
		std::cout << "int: impossible\n";
	else
		std::cout << "int: " << static_cast<int>(number) << '\n';
	//	check max and min float
	if (number > FLT_MAX || number < -FLT_MAX)
		std::cout << "float: impossible\n";
	else if (has_decimal_value(number) || number >= 1000000) // if number is greater than 100000 will be displayed in scientific notation
		std::cout << "float: " << static_cast<float>(number) << "f\n";
	else
		std::cout << "float: " << static_cast<float>(number) << ".0f\n";
	if (has_decimal_value(number) || number >= 1000000)
		std::cout << "double: " << number << '\n';
	else
		std::cout << "double: " << number << ".0\n";
}

void	display_from_special_case(std::string arg)
{
	float	number;

	std::cout << "char: impossible\nint: impossible\n";
	if (arg == "inf" || arg == "+inf" || arg == "inff" || arg == "+inff")
		number = 1.0 / 0.0;
	else if (arg == "-inf" || arg == "-inff")
		number = -1.0 / 0.0;
	else
		number = 0.0 / 0.0;
	std::cout << "float: " << number << "f\ndouble: " << static_cast<double>(number) << '\n';
}
