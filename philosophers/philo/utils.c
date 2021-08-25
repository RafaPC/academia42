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
