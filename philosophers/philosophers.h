#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef enum e_message_type
{
	fork_taken,
	eating,
	sleeping,
	thinking
}			t_message_type;

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
	int		min_eating_times;
	long	starting_time;
}				t_philosophers_info;

t_bool				g_end;
pthread_mutex_t		*g_forks;
int					*g_meals;
pthread_mutex_t		g_print_mutex;
long				*g_time_last_meal;
t_philosophers_info	g_info;

/*
**		READ PARAMETERS
*/
t_bool	read_parameters(const int argc, char const *argv[]);

/*
**		PHILOSOPHER ROUTINE
*/
void	*philosopher_routine(void *param);

/*
**		UTILS
*/
long	get_current_timestamp(void);
t_bool	all_have_eaten(void);
void	print_status_message(int philo_id, t_message_type message_type);
void	safe_sleep(int	miliseconds);
#endif