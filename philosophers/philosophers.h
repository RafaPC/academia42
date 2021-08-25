#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>

pthread_mutex_t		*g_forks;
int					*g_philosophers_meals;
pthread_mutex_t		g_print_mutex;
long				*g_time_last_meal;

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_philosophers_info
{
	int		philo_size;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_eating_times;
	long	starting_time;
}				t_philosophers_info;

t_philosophers_info	g_info;

/*
**		READ PARAMETERS
*/

t_bool	read_parameters(const int argc, char const *argv[]);

/*
**		PHILOSOPHER ACTIONS
*/

void	*philosopher_routine(void *param);
t_bool	all_have_eaten(void);

/*
**		UTILS
*/

long	get_current_timestamp(void);
long	get_pretty_timestamp(long starting_time);
#endif