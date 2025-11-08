#ifndef PHILO_C
#define PHILO_C

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// Filosof holatlari
# define THINKING 0
# define SLEEPING 1

typedef struct s_philo
{
	int			id;
	int			state;
	long		start_time;
	pthread_t	thread;
}	t_philo;

typedef struct s_data
{
	int	num_philo;
	t_philo	*philolo;
} t_data;

void	join_threads(t_data *data);
long	get_current_time();
void	create_threads(t_data *data);
void*	philo_life(void *arg);
void	init(t_data *data, int num_philo);
void	print_state(t_philo *philo, const char *state);

#endif
