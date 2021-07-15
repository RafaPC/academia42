#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "philosophers.h"

/*
**		Kills the philosopher,
**		unlocks the forks it had locked,
**		prints the message and exists
*/
void	die(int id, int option, pthread_mutex_t	*philo_forks[2])
{
	if (option == 1)
		pthread_mutex_unlock(philo_forks[0]);
	else if (option == 2)
	{
		pthread_mutex_unlock(philo_forks[0]);
		pthread_mutex_unlock(philo_forks[1]);
	}
	printf("%ld %d died\n", get_current_timestamp(), id);
	exit(0);
}

/*
**	Returns true if the philosopher should die
*/
t_bool	should_die(long last_time_eat, int time_to_die)
{
	if (get_current_timestamp() - last_time_eat > time_to_die)
		return (true);
	else
		return (false);
}