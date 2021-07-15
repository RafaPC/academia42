#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // printf()
#include <unistd.h> // usleep()
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
**	Según empieza intenta coger los dos tenedores, come, duerme, repite
**	FIXME: checkearque si solo hay 1 filósofo solo hay 1 tenedor
*/
void	*philosopher_routine(void *param)
{
	const t_philosopher	philosopher = *(t_philosopher*)param;
	pthread_mutex_t		*philo_forks[2];
	long last_time_eat;

	last_time_eat = get_current_timestamp();
	printf("Philosopher %d is alive\n", philosopher.id + 1);

	if (philosopher.id == 0)
	{
		philo_forks[0] = &g_forks[philosopher.info.philo_size - 1];
		philo_forks[1] = &g_forks[0];
	}
	else if (philosopher.id == philosopher.info.philo_size - 1)
	{
		philo_forks[0] = &g_forks[philosopher.id - 1];
		philo_forks[1] = &g_forks[philosopher.id];
	}
	else
	{
		philo_forks[0] = &g_forks[philosopher.id - 1];
		philo_forks[1] = &g_forks[philosopher.id];
	}
	while (true)
	{
		if (should_die(last_time_eat, philosopher.info.time_to_die))
			die(philosopher.id, 0, philo_forks);
		pthread_mutex_lock(philo_forks[0]);
		printf("%ld %d has taken a fork\n", get_current_timestamp(), philosopher.id + 1);
		if (should_die(last_time_eat, philosopher.info.time_to_die))
			die(philosopher.id, 1, philo_forks);
		pthread_mutex_lock(philo_forks[1]);
		printf("%ld %d has taken a fork\n", get_current_timestamp(), philosopher.id + 1);
		if (should_die(last_time_eat, philosopher.info.time_to_die))
			die(philosopher.id, 2, philo_forks);
		printf("%ld %d is eating\n", get_current_timestamp(), philosopher.id + 1);
		last_time_eat = get_current_timestamp();
		usleep(philosopher.info.time_to_eat * 1000);
		pthread_mutex_unlock(philo_forks[0]);
		pthread_mutex_unlock(philo_forks[1]);
		if (should_die(last_time_eat, philosopher.info.time_to_die))
			die(philosopher.id, 0, philo_forks);
		printf("%ld %d is sleeping\n", get_current_timestamp(), philosopher.id + 1);
		usleep(philosopher.info.time_to_sleep * 1000);
		if (should_die(last_time_eat, philosopher.info.time_to_die))
			die(philosopher.id, 0, philo_forks);
		printf("%ld %d is thinking\n", get_current_timestamp(), philosopher.id + 1);
	}

	return (param);
}

int main(int argc, char const *argv[])
{
	t_philosophers_info info;
	pthread_t	*philosophers_threads;
	t_philosopher *philosophers;

	if (read_parameters(&info, argc, argv))
	{
		printf("Parámetros leídos correctamente\n");
		philosophers_threads = (pthread_t*)malloc(sizeof(pthread_t) * info.philo_size);
		g_forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * info.philo_size);
		philosophers = (t_philosopher*)malloc(sizeof(t_philosopher) * info.philo_size);
		
		//Inicializa un mutex por cada tenedor
		for (int i = 0; i < info.philo_size; i++)
			pthread_mutex_init(&g_forks[i], NULL);
		
		//Rellena los structs y crea los hilos mándandoles su struct
		for (int i = 0; i < info.philo_size; i++)
		{
			//Relleno el struct con la informacion general y la id del filósofo
			philosophers[i].info = info;
			philosophers[i].id = i;
			//Creo el hilo pasándole la dirección del hilo correspondiente
			pthread_create(&philosophers_threads[i], NULL, philosopher_routine, (void*)&philosophers[i]);
		}
		//Espero a todos los hilos
		for (int i = 0; i < info.philo_size; i++)
			pthread_join(philosophers_threads[i], NULL);
		exit(0);
	}
	else
		printf("Error al leer parámetros");
	return (0);
}
