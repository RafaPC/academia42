#include "philosophers.h"

static int	ft_atoi(const char *str)
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

t_bool	read_parameters(t_philosophers_info *philo_info, const int argc, char const *argv[])
{
	if (argc != 5 && argc != 6)
		return (false);
	philo_info->philo_size = ft_atoi(argv[1]);
	philo_info->time_to_die = ft_atoi(argv[2]);
	philo_info->time_to_eat = ft_atoi(argv[3]);
	philo_info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_info->max_eating_times = ft_atoi(argv[5]);
	if (philo_info->philo_size == -1 || philo_info->time_to_die == -1
		|| philo_info->time_to_eat == -1 || philo_info->time_to_sleep == -1
		|| (argc == 6 && philo_info->max_eating_times == -1))
		return (false);
	else
		return (true);
}
