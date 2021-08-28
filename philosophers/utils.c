#include <sys/time.h> // gettimeofday()
#include "philosophers.h"

/*
**	Gets the current timestamp in milliseconds
*/
long	get_current_timestamp(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

/*
**	Returns the number of miliseconds that has passed
**	since the start of the program
*/
long	get_pretty_timestamp(long starting_time)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms - starting_time);
}

/*
**	Returns true if every philosopher have eaten at least n times
*/
t_bool	all_have_eaten(void)
{
	int	i;

	i = 0;
	while (i < g_info.philo_size)
	{
		if (g_philosophers_meals[i] < g_info.min_eating_times)
			return (false);
		i++;
	}
	return (true);
}
