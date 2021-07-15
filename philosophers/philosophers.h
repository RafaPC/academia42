#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
pthread_mutex_t	*g_forks;

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
}				t_philosophers_info;

typedef struct s_philosopher
{
	t_philosophers_info info;
	int					id;
}				t_philosopher;

/*
**		READ PARAMETERS
*/
t_bool read_parameters(t_philosophers_info *philo_info, const int argc, char const *argv[]);
long	get_current_timestamp(void);

/*
**		PHILOSOPHER ACTIONS
*/
t_bool	should_die(long last_time_eat, int time_to_die);
void	die(int id, int option, pthread_mutex_t	*philo_forks[2]);
#endif