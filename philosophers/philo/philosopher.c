#include <pthread.h>
#include <stdio.h>	// printf()
#include <unistd.h>	// usleep()
#include "philosophers.h"


/*
** TODO:
*/
t_bool	eat(int id, pthread_mutex_t *philo_forks[2], long *last_time_eat)
{
	if (g_dead)
		return (die(id, 0, philo_forks));
	pthread_mutex_lock(philo_forks[0]);
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d has taken a fork\n", get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	if (should_die(*last_time_eat, g_info.time_to_die))
		return (die(id, 1, philo_forks));
	pthread_mutex_lock(philo_forks[1]);
	if (g_dead)
		return (die(id, 2, philo_forks));
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d has taken a fork\n", get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	if (should_die(*last_time_eat, g_info.time_to_die))
		return (die(id, 2, philo_forks));
	// if (g_dead)
	// 	usleep(1000000);
	// Antes de comer mirar si el tiempo de comer es mayor que el de morir
	*last_time_eat = get_current_timestamp();
	// FIXME: MIRAR ESTO BIEN
	if (get_current_timestamp() - *last_time_eat + g_info.time_to_eat > g_info.time_to_die)
	{
		usleep((g_info.time_to_die - (get_current_timestamp() - *last_time_eat)) * 1000);
		return (die(id, 2, philo_forks));
	}
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d is eating\n", get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	// if ((get_current_timestamp() - *last_time_eat + g_info.time_to_eat) > g_info.time_to_die) //FIXME: aqui checkear el tiempo que ha pasado desde la ultima comida
	// {
	// 	if ((get_current_timestamp() - *last_time_eat) < g_info.time_to_die)
	// 		usleep((g_info.time_to_die - (get_current_timestamp() - *last_time_eat)) * 1000);
	// 	die(id, 2, philo_forks);
	// 	return (false);
	// }
	// *last_time_eat = get_current_timestamp();
	usleep(g_info.time_to_eat * 1000);
	// pthread_mutex_unlock(philo_forks[0]);
	// pthread_mutex_unlock(philo_forks[1]);
	if (g_info.max_eating_times != -1)
		g_philosophers_meals[id]++;
	if (g_info.max_eating_times != -1)
	{
		if (all_have_eaten())
		{
			g_dead = true;
			return (die(id, 2, philo_forks));
		}
	}
	return (true);
}

/*
**	Returns true if all the philosophers have eat at least eaten n times
*/
t_bool	all_have_eaten(void)
{
	int	i;

	i = 0;
	if (g_info.max_eating_times == -1)
		return (false);
	while (i < g_info.philo_size)
	{
		if (g_philosophers_meals[i] < g_info.max_eating_times)
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
t_bool	die(int id, int option, pthread_mutex_t	*philo_forks[2])
{
	if (option == 1)
		pthread_mutex_unlock(philo_forks[0]);
	else if (option == 2)
	{
		pthread_mutex_unlock(philo_forks[0]);
		pthread_mutex_unlock(philo_forks[1]);
	}
	if (!g_dead)
	{
		pthread_mutex_lock(&g_print_mutex);
		printf("%ld %d died\n", get_pretty_timestamp(g_info.starting_time), id + 1);
		// pthread_mutex_unlock(&g_print_mutex);
	}
	g_dead = true;
	return (false);
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
t_bool	ft_sleep(int id, pthread_mutex_t *philo_forks[2], long last_time_eat)
{
	//Dejo el mutex del printeo bloqueado
	if (g_dead)
		return (false);
	// if (g_info.philo_size == 2)
		// write(STDOUT_FILENO, "va a dormir\n", 12);
	pthread_mutex_lock(&g_print_mutex);
	printf("%ld %d is sleeping\n", get_pretty_timestamp(g_info.starting_time), id + 1);
	pthread_mutex_unlock(&g_print_mutex);
	// if (g_info.philo_size == 2)
		// write(STDOUT_FILENO, "ha dormido\n", 11);
	usleep(2000);
	pthread_mutex_unlock(philo_forks[0]);
	pthread_mutex_unlock(philo_forks[1]);
	//Antes de dormir hay que checkear si le tocaría morir mientras duerme
	if (get_current_timestamp() - last_time_eat + g_info.time_to_sleep > g_info.time_to_die)
	{
		usleep((g_info.time_to_die - (get_current_timestamp() - last_time_eat)) * 1000);
		return (die(id, 0, philo_forks));
	}
	usleep(g_info.time_to_sleep * 1000);
	return (true);
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
	// printf("Philosopher %d is alive\n", id + 1);
	asign_forks(id, philo_forks);
	while (true)
	{
		//Checkear si en 10 milisegundos tiene que morir aprox
		if (get_current_timestamp() - last_time_eat > (g_info.time_to_die - 10))
		{
			usleep((g_info.time_to_die - (get_current_timestamp() - last_time_eat)) * 1000);
			return ((void *) die(id, 0, philo_forks));
		}
		if (should_die(last_time_eat, g_info.time_to_die))
			return ((void *) die(id, 0, philo_forks));
		if (!eat(id, philo_forks, &last_time_eat))
			return (0);
		if (should_die(last_time_eat, g_info.time_to_die))
			return ((void *) die(id, 2, philo_forks));
		ft_sleep(id, philo_forks, last_time_eat);
		if (should_die(last_time_eat, g_info.time_to_die))
			return ((void *) die(id, 0, philo_forks));
		pthread_mutex_lock(&g_print_mutex);
		printf("%ld %d is thinking\n", get_pretty_timestamp(g_info.starting_time), id + 1);
		pthread_mutex_unlock(&g_print_mutex);
	}

	return (param);
}