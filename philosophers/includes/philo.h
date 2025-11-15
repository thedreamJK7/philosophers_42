/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:55:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/15 18:42:50 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MIN_PHILO 1
# define MAX_PHILO 200
# define MIN_TIME 60
# define MAX_TIME 600000
# define MAX_EAT 1000
# define MAX_DIGIT 6

# define INVALID_INPUT_MSG "Invalid INPUT: 1.number_of_philosophers \
2.time_to_die 3.time_to_eat 4.time_to_sleep \
5.[number_of_times_each_philosopher_must_eat]\n"

# define ERROR_MUTEX_INIT "Error: Mutex initialization failed\n"
# define ERROR_THREAD_CREATE "Error: Failed to create thread\n"
# define ERROR_MEMORY_ALLOC "Error: Memory allocation failed\n"
# define ERROR_POSITIVE_INT "Error: All arguments must be positive integers\n"
# define ERROR_N_PHILOS "Error: Number of philosophers must be between 1-200\n"
# define ERROR_TIME_DIE "Error: time_to_die must be between 60-600000 ms\n"
# define ERROR_NUM_MEALS "Error: num_meals must be between 1-1000\n"
# define ERROR_CREATE_PHILO_T "Error: Failed to create philosopher threads\n"
# define ERROR_JOIN_PHILO_T "Error: Failed to join philosopher threads\n"
# define ERROR_CREATE_MONITOR_T "Error: Failed to create monitor thread\n"
# define ERROR_JOIN_MONITOR_T "Error: Failed to join monitor thread\n"

# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	int				meals_eaten;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	last_meal_time_mutex;
}				t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				someone_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	someone_died_mutex;
	t_philo			*philos;
	pthread_t		monitor_routine;
}				t_data;

int			ft_atoi(const char *str);
void		ft_putstr_fd(const char *s, int fd);
int			is_number(char *str);
long long	get_time_in_ms(void);
void		ft_usleep(long long time_in_ms);
void		print_action(t_philo *philo, const char *action);
int			init_data(t_data *data, int argc, char **argv);
void		destroy_data(t_data *data);
void		*philo_routine(void *arg);
int			init_forks(t_data *data);
int			validate_args(int argc, char **argv);
void		*monitor_routine(void *arg);
void		cleanup(t_data *data);
void		destroy_single_mutex(pthread_mutex_t *mutex);
void		destroy_fork_mutexes(t_data *data, int num);
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);
int			create_philo_threads(t_data *data);
int			read_someone_died(t_data *data);
int			thread_join_philosophers(t_data *data);

#endif