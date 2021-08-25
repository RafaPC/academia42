#include <pthread.h>
#include <stdio.h>	// printf()
#include <unistd.h>	// usleep()
#include "philosophers.h"

/*
** TODO:
*/
void	eat(int id, pthread_mutex_t *philo_forks[2])
{
	pthread_mutex_lock(philo_forks[0]);
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d has taken a fork\n",
		get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	pthread_mutex_lock(philo_forks[1]);
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d has taken a fork\n",
		get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	g_time_last_meal[id] = get_current_timestamp();
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d is eating\n",
		get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	usleep(g_info.time_to_eat * 1000);
	if (g_info.max_eating_times != -1)
		g_philosophers_meals[id]++;
}

void	asign_forks(int id, pthread_mutex_t	*philo_forks[2])
{
	if (id == 0)
	{
		philo_forks[0] = &g_forks[g_info.philo_size - 1];
		philo_forks[1] = &g_forks[0];
	}
	else if (id == g_info.philo_size - 1)
	{
		philo_forks[0] = &g_forks[id - 1];
		philo_forks[1] = &g_forks[id];
	}
	else
	{
		philo_forks[0] = &g_forks[id - 1];
		philo_forks[1] = &g_forks[id];
	}
}

/*
**	TODO: TRIES TO SLEEP CHECKING THE TIME
*/
t_bool	philo_sleep(int id, pthread_mutex_t *philo_forks[2])
{
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d is sleeping\n",
		get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	pthread_mutex_unlock(philo_forks[0]);
	pthread_mutex_unlock(philo_forks[1]);
	usleep(g_info.time_to_sleep * 1000);
	return (true);
}

/*
**	Según empieza intenta coger los dos tenedores, come, duerme, repite
*/
void	*philosopher_routine(void *param)
{
	const int			id = *(int*)param;
	pthread_mutex_t		*philo_forks[2];

	g_time_last_meal[id] = get_current_timestamp();
	asign_forks(id, philo_forks);
	while (true)
	{
		eat(id, philo_forks);
		philo_sleep(id, philo_forks);
		pthread_mutex_lock(&g_print_mutex);
		printf("%ld %d is thinking\n",
			get_pretty_timestamp(g_info.starting_time), id + 1);
		pthread_mutex_unlock(&g_print_mutex);
	}
	return (NULL);
}
