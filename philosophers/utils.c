#include <sys/time.h>	// gettimeofday()
#include <stdio.h>		// printf()
#include <unistd.h>		// usleep()
#include "philosophers.h"

/*
**	Returns the current timestamp in milliseconds
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
**	Returns true if every philosopher has eaten at least n times
*/
t_bool	all_have_eaten(void)
{
	int	i;

	i = 0;
	while (i < g_info.philo_size)
	{
		if (g_meals[i] < g_info.min_eating_times)
			return (false);
		i++;
	}
	return (true);
}

/*
**	Prints a message showing the miliseconds passed since the start,
**	the id of the philo and the action
**	If g_end (variable set when the program is ending) is set to true
**	it returns inmediatly and doesn't print he message
*/
void	print_status_message(int philo_id, t_message_type message_type)
{
	const long	current_time = get_current_timestamp() - g_info.starting_time;

	if (g_end)
		return ;
	pthread_mutex_lock(&g_print_mutex);
	if (message_type == fork_taken)
		printf("%ld %d has taken a fork\n", current_time, philo_id);
	else if (message_type == eating)
		printf("%ld %d is eating\n", current_time, philo_id);
	else if (message_type == sleeping)
		printf("%ld %d is sleeping\n", current_time, philo_id);
	else if (message_type == thinking)
		printf("%ld %d is thinking\n", current_time, philo_id);
	pthread_mutex_unlock(&g_print_mutex);
}

/*
**	Sleeps the amount received by parameters checking every 100 miliseconds
**	in case the program has ended and the thread should die
**	This is because before ending the program, the main thread waits for every
**	philosopher thread to end
*/
void	safe_sleep(int	miliseconds)
{
	while (miliseconds > 0)
	{
		if (g_end)
			return ;
		if (miliseconds > 100)
			usleep(100000);
		else
			usleep(miliseconds * 1000);
		miliseconds -= 100;
	}
}
