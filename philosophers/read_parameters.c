#include <stdio.h>	// printf()
#include "philosophers.h"

/*
**	Atoi that returns -1 if the number has any symbol that is not a digit
*/
static int	no_symbol_atoi(const char *str)
{
	int		i;
	int		number;

	i = 0;
	number = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number == 0)
			number = str[i] - 48;
		else
			number = number * 10 + str[i] - 48;
		i++;
	}
	if (str[i] == '\0')
		return (number);
	else
		return (-1);
}

/*
**	If the number of parameters is correct, it sends every argument to an atoi
**	to get its numeric value and then checks if all the values were well written
**	If any of them had a non-digit symbol, atoi returned -1 and the function
**	will return false
*/
t_bool	read_parameters(const int argc, char const *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments, must be 4 or 5 arguments\n");
		return (false);
	}
	g_info.philo_size = no_symbol_atoi(argv[1]);
	g_info.time_to_die = no_symbol_atoi(argv[2]);
	g_info.time_to_eat = no_symbol_atoi(argv[3]);
	g_info.time_to_sleep = no_symbol_atoi(argv[4]);
	if (argc == 6)
		g_info.min_eating_times = no_symbol_atoi(argv[5]);
	else
		g_info.min_eating_times = -1;
	if (g_info.philo_size == -1 || g_info.time_to_die == -1
		|| g_info.time_to_eat == -1 || g_info.time_to_sleep == -1
		|| (argc == 6 && g_info.min_eating_times == -1))
		return (false);
	else
		return (true);
}
