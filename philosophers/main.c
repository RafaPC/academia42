#include <pthread.h>
#include <stdlib.h> // malloc()
#include <stdio.h> // printf()
#include <unistd.h> // usleep()
#include <string.h> // memset()
#include "philosophers.h"

t_bool	create_philosophers(int *ids, pthread_t *philosophers_threads);
void	manage_philosophers_lifes(void);
void	free_variables(int *ids, pthread_t *philosophers_threads);

/*
**	All pointers are set to NULL value at the start
**	Then the pointers memory is allocated and if any of them returned NULL
**	the function ends returning false
**	If all the memory was correctly allocated, the mutexes are initialiced
**	and also checked wether they are created correctly or not
*/
t_bool	initialice_variables(int **ids, pthread_t **philosophers_threads)
{
	int	i;

	i = 0;
	g_info.starting_time = get_current_timestamp();
	*philosophers_threads = (pthread_t *)malloc(
			sizeof(pthread_t) * g_info.philo_size);
	g_forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * g_info.philo_size);
	*ids = (int *) malloc(sizeof(int) * g_info.philo_size);
	g_time_last_meal = (long *) malloc(sizeof(long) * g_info.philo_size);
	if (!*philosophers_threads || !g_forks || !*ids || !g_time_last_meal)
		return (false);
	memset(g_time_last_meal, 0, sizeof(long));
	if (pthread_mutex_init(&g_print_mutex, NULL))
		return (false);
	while (i < g_info.philo_size)
	{
		if (pthread_mutex_init(&g_forks[i], NULL))
			return (false);
		i++;
	}
	return (true);
}

/*
**	Reads the parameters, initialices the variables, creates the threads and 
*/
int	main(int argc, char const *argv[])
{
	pthread_t	*philosophers_threads;
	int			*ids;

	if (!read_parameters(argc, argv))
		return (0);
	if (g_info.min_eating_times != -1)
	{
		g_philosophers_meals = (int *) malloc(sizeof(int) * g_info.philo_size);
		memset(g_philosophers_meals, 0, sizeof(int) * g_info.philo_size);
	}
	if (initialice_variables(&ids, &philosophers_threads)
		&& create_philosophers(ids, philosophers_threads))
		manage_philosophers_lifes();
	free_variables(ids, philosophers_threads);
	return (0);
}

/*
**	Iterates as many times as philosophers must be created
**	Each time, the counter is stored in an array so it can be passed
**	to the philosopher as his id
**	Then, the philosopher is created and then detached so its resources will
**	be released to the system when the program ends
**	It waits 1 milisecond between each iteration to prevent philosophers
**	from getting stuck with 1 fork each
*/
t_bool	create_philosophers(int *ids, pthread_t *philosophers_threads)
{
	int	i;

	i = 0;
	while (i < g_info.philo_size)
	{
		ids[i] = i;
		if (pthread_create(
				&philosophers_threads[i], NULL, philosopher_routine, &ids[i])
			|| pthread_detach(philosophers_threads[i]))
			return (false);
		usleep(1000);
		i++;
	}
	return (true);
}

/*
**	This function iterates until a philosopher dies or until every philosopher
**	has eaten at least the minimum amount (if the parameter is set)
**	Each time, it iterates as many times as philosophers there are and
**	calculates how much time has passed since his last meal to check
**	if it should die or not
*/
void	manage_philosophers_lifes(void)
{
	long	current_time;
	int		i;

	while (true)
	{
		current_time = get_current_timestamp();
		i = 0;
		while (i < g_info.philo_size)
		{
			if (current_time - g_time_last_meal[i] > g_info.time_to_die)
			{
				pthread_mutex_lock(&g_print_mutex);
				printf("%ld %d died\n",
					get_pretty_timestamp(g_info.starting_time), i + 1);
				return ;
			}
			else if (g_info.min_eating_times != -1 && all_have_eaten())
			{
				pthread_mutex_lock(&g_print_mutex);
				return ;
			}
			i++;
		}
	}
}

/*
** It destroy all the mutexes and frees every variable that has been allocated
*/
void	free_variables(int *ids, pthread_t *philosophers_threads)
{
	int	i;

	i = 0;
	while (i < g_info.philo_size)
		pthread_mutex_destroy(&g_forks[i++]);
	pthread_mutex_destroy(&g_print_mutex);
	if (g_time_last_meal)
		free(g_time_last_meal);
	if (g_philosophers_meals)
		free(g_philosophers_meals);
	if (philosophers_threads)
		free(philosophers_threads);
	if (g_forks)
		free(g_forks);
	if (ids)
		free(ids);
}
