#include <string>
#include <iostream>
#include "convert.hpp"

void	print_char(char character)
{
	if (isprint(character))
		std::cout << "char: '" << character << "'\n";
	else
		std::cout << "char: " << "Non displayable\n";
}


bool	has_decimal_value(double number)
{
	if (number < 0.0)
		number = -number;

	while (number >= 10000.0)
		number = number - 10000.0;
	while (number >= 1.0)
		number = number - 1.0;
	return (number > 0.0 ? true : false);
}