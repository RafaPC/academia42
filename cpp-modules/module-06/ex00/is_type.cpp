#include <string>
#include "convert.hpp"

bool is_integer(std::string arg)
{
	int i = 0;

	if (arg[0] == '+' || arg[0] == '-')
		i++;
	for (; arg[i]; i++)
	{
		if (!isdigit(arg[i]))
			return (false);
	}
	return (true);
}

/*
**	0. and .0 are valid, that's why the has_number bool is used
*/
int is_point_value(std::string arg)
{
	int i = 0;

	if (arg.find('.') == arg.npos) //it must have a point
		return (false);
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	while (isdigit(arg[i]))
		i++;
	if (arg[i] == '.')
		i++;
	else
		return (false);
	while (isdigit(arg[i]))
		i++;
	if (arg[i] == 'f' && arg[i + 1] == '\0')
		return (float_type);
	else if (arg[i] == '\0')
		return (double_type);
	else
		return (0);
}

bool is_special_case(std::string arg)
{
	if (arg == "nan" || arg == "nanf" || arg == "inf" || arg == "+inf" ||
		arg == "inff" || arg == "+inff" || arg == "-inf" || arg == "-inff")
		return (true);
	else
		return (false);
}