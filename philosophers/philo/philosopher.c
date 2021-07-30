#include <pthread.h>
#include <stdio.h>	// printf()
#include <unistd.h>	// usleep()
#include "philosophers.h"


/*
** TODO:
*/
t_bool	eat(int id, pthread_mutex_t *philo_forks[2], int *last_time_eat)
{
	pthread_mutex_lock(philo_forks[0]);
	printf("%ld %d has taken a fork\n", get_current_timestamp(), id + 1);
	if (should_die(*last_time_eat, g_info.time_to_die))
	{
		die(id, 1, philo_forks);
		return (0);
	}
	pthread_mutex_lock(philo_forks[1]);
	printf("%ld %d has taken a fork\n", get_current_timestamp(), id + 1);
	if (should_die(*last_time_eat, g_info.time_to_die))
	{
		die(id, 2, philo_forks);
		return (0);
	}
	printf("%ld %d is eating\n", get_current_timestamp(), id + 1);
	if (get_current_timestamp() - *last_time_eat + g_info.time_to_eat > g_info.time_to_die) //FIXME: aqui checkear el tiempo que ha pasado desde la ultima comida
	{
		if ((get_current_timestamp() - *last_time_eat) < g_info.time_to_die)
			usleep((g_info.time_to_die - get_current_timestamp() - *last_time_eat) * 1000);
		die(id, 2, philo_forks);
		return (false);
	}
	*last_time_eat = get_current_timestamp();
	usleep(g_info.time_to_eat * 1000);
	pthread_mutex_unlock(philo_forks[0]);
	pthread_mutex_unlock(philo_forks[1]);
	g_philosophers_meals[id]++;
	if (g_info.max_eating_times != -1)
	{
		if (all_have_eaten())
		{
			die(id, 0, philo_forks);
			return (0);
		}
	}
}

/*
**	Returns true if all the philosophers have eat at least eaten n times
*/
t_bool	all_have_eaten(void)
{
	int	i;

	i = 0;
	while (i < g_info.philo_size)
	{
		if (g_philosophers_meals[0] < g_info.max_eating_times)
			return (false);
		i++;
	}
	return (true);
}

/*
**	Kills the philosopher,
**	unlocks the forks it had locked,
**	prints the message and exists
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
	if (!g_dead && !all_have_eaten())
		printf("%ld %d died\n", get_current_timestamp(), id + 1);
	g_dead = true;
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
**	Según empieza intenta coger los dos tenedores, come, duerme, repite
**	FIXME: checkearque si solo hay 1 filósofo solo hay 1 tenedor
*/
void	*philosopher_routine(void *param)
{
	const int			id = *(int*)param;
	pthread_mutex_t		*philo_forks[2];
	long				last_time_eat;

	last_time_eat = get_current_timestamp();
	printf("Philosopher %d is alive\n", id + 1);
	asign_forks(id, philo_forks);
	while (true)
	{
		if (should_die(last_time_eat, g_info.time_to_die))
		{
			die(id, 0, philo_forks);
			return (0);
		}
		if (!eat(id, philo_forks, &last_time_eat))
			return (0);
		if (should_die(last_time_eat, g_info.time_to_die))
		{
			die(id, 0, philo_forks);
			return (0);
		}
		printf("%ld %d is sleeping\n", get_current_timestamp(), id + 1);
		usleep(g_info.time_to_sleep * 1000);
		if (should_die(last_time_eat, g_info.time_to_die))
		{
			die(id, 0, philo_forks);
			return (0);
		}
		printf("%ld %d is thinking\n", get_current_timestamp(), id + 1);
	}

	return (param);
}