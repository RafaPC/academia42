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
**	Returns true if the philosopher should die
*/
t_bool	should_die(long last_time_eat, int time_to_die)
{
	if (get_current_timestamp() - last_time_eat > time_to_die || (g_dead))
		return (true);
	else
		return (false);
}
