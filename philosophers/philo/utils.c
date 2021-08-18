#include <sys/time.h> // gettimeofday()
#include "philosophers.h"
#include <unistd.h> // usleep()
#include <stdio.h> // printf()

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
**	Gets the current timestamp in milliseconds
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
**	Returns true if the philosopher should die
*/
t_bool	should_die(long last_time_eat, int time_to_die)
{
	const long timestamp = get_current_timestamp();

	if (timestamp - last_time_eat > (time_to_die - 3) || (g_dead))
	{

		if (!g_dead && (time_to_die > (timestamp - last_time_eat)))
		{
			// printf("Duerme %ld antes de morir\n", time_to_die - (timestamp - last_time_eat));
			usleep((time_to_die - (timestamp - last_time_eat)) * 1000);
		}
		return (true);
	}
	else
		return (false);
}
