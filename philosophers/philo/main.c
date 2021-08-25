#include <pthread.h>
#include <stdlib.h> // malloc()
#include <stdio.h> // printf()
#include "philosophers.h"
#include <unistd.h> // usleep()

void	create_philosophers(int *ids, pthread_t *philosophers_threads);
void	check_philosophers_lifes(void);

/*
**	FIXME: CHECKEAR LOS PUNTEROS NULOS Y ESO
*/
t_bool	initialice_variables(int **ids, pthread_t **philosophers_threads)
{
	*philosophers_threads = NULL;
	g_forks = NULL;
	*ids = NULL;
	g_time_last_meal = NULL;

	// Doy valor a starting time
	g_info.starting_time = get_current_timestamp();
	*philosophers_threads = (pthread_t*)malloc(sizeof(pthread_t) * g_info.philo_size);
	g_forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * g_info.philo_size);
	*ids = (int*) malloc(sizeof(int) * g_info.philo_size);
	g_time_last_meal = (long*) malloc(sizeof(long) * g_info.philo_size);
	
	if (pthread_mutex_init(&g_print_mutex, NULL) == -1)
		return (false);
	//Inicializa un mutex por cada tenedor
	for (int i = 0; i < g_info.philo_size; i++)
		if (pthread_mutex_init(&g_forks[i], NULL) == -1)
			return (false);
	return (true);
}

int main(int argc, char const *argv[])
{
	pthread_t	*philosophers_threads;
	int			*ids;

	if (!read_parameters(argc, argv))
		return (0);
	if (g_info.max_eating_times != -1)
	{
		g_philosophers_meals = (int*) malloc(sizeof(int) * g_info.philo_size);
		for (int i = 0; i < g_info.philo_size; i++)
			g_philosophers_meals[i] = 0;
	}
	if (!initialice_variables(&ids, &philosophers_threads))
	{
		free_variables(ids, philosophers_threads);
		return (0);
	}
	create_philosophers(ids, philosophers_threads);
	check_philosophers_lifes();
	free_variables(ids, philosophers_threads);
	return (0);
}


/*
**	TODO:
*/
void	create_philosophers(int *ids, pthread_t *philosophers_threads)
{
	int	i;

	i = 0;
	while (i < g_info.philo_size)
	{
		ids[i] = i;
		pthread_create(&philosophers_threads[i], NULL, philosopher_routine, &ids[i]);
		pthread_detach(philosophers_threads[i]);
		usleep(1000);
		i++;
	}
}

/*
**	TODO:
*/
void	check_philosophers_lifes(void)
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
				printf("%ld %d died\n", get_pretty_timestamp(g_info.starting_time), i + 1);
				return ;
			}
			else if (g_info.max_eating_times != -1 && all_have_eaten())
			{
				pthread_mutex_lock(&g_print_mutex);
				return ;
			}
			i++;
		}
	}
}

/*
** TODO:
*/
void	free_variables(int *ids, pthread_t *philosophers_threads)
{

	for (int i = 0; i < g_info.philo_size; i++)
		pthread_mutex_destroy(&g_forks[i]);
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

/*
**	Returns true if all the philosophers have eat at least eaten n times
*/
t_bool	all_have_eaten(void)
{
	int	i;

	i = 0;
	while (i < g_info.philo_size)
	{
		if (g_philosophers_meals[i] < g_info.max_eating_times)
			return (false);
		i++;
	}
	return (true);
}
