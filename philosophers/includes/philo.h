/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:55:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/12 18:54:10 by javokhir         ###   ########.fr       */
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
	t_philo			*philos;
}				t_data;

int			ft_atoi(const char *str);
void 		ft_putstr_fd(const char *s, int fd);
int			is_number(char *str);
long long	get_time_in_ms(void);
void		ft_usleep(long long time_in_ms);
void		print_action(t_philo *philo, const char *action);
int			init_data(t_data *data, int argc, char **argv);
void		destroy_data(t_data *data);
void		*philo_routine(void *arg);
int			init_forks(t_data *data);
int			validate_args(int argc, char **argv);

/* cleanups */
void	cleanup(t_data *data);
void	destroy_single_mutex(pthread_mutex_t *mutex);
void    destroy_fork_mutexes(t_data *data, int num);

#endif