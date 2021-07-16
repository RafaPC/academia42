#include <pthread.h>
#include <stdlib.h> // malloc()
#include <stdio.h> // printf()
#include "philosophers.h"

int main(int argc, char const *argv[])
{
	pthread_t	*philosophers_threads;
	int			*ids;

	if (read_parameters(argc, argv))
	{
		//Si tienen argumento de numero de comidas, se hace todo esto
		if (g_info.max_eating_times != -1)
		{
			g_philosophers_meals = (int*) malloc(sizeof(int) * g_info.philo_size);
			for (int i = 0; i < g_info.philo_size; i++)
				g_philosophers_meals[i] = 0;
		}

		//FIXME: checkear que no devuelve nulo y eso
		philosophers_threads = (pthread_t*)malloc(sizeof(pthread_t) * g_info.philo_size);
		g_forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * g_info.philo_size);
		ids = (int*) malloc(sizeof(int) * g_info.philo_size);

		//Inicializa un mutex por cada tenedor
		for (int i = 0; i < g_info.philo_size; i++)
			pthread_mutex_init(&g_forks[i], NULL);
		
		//Rellena los structs y crea los hilos mándandoles su struct
		//Creo el hilo pasándole la dirección del hilo correspondiente
		for (int i = 0; i < g_info.philo_size; i++)
		{
			ids[i] = i;
			pthread_create(&philosophers_threads[i], NULL, philosopher_routine, &ids[i]);
			pthread_detach(philosophers_threads[i]);
		}
		//Espero a todos los hilos
		// for (int i = 0; i < g_info.philo_size; i++)
		// 	pthread_join(philosophers_threads[i], NULL);
		while (!g_dead)
		{

		}
		for (int i = 0; i < g_info.philo_size; i++)
			pthread_mutex_destroy(&g_forks[i]);
		free(g_philosophers_meals);
		free(philosophers_threads);
		free(g_forks);
		return (0);
	}
	else
		printf("Error al leer parámetros");
	return (0);
}
