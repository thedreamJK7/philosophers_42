/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:32:06 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/12 21:48:07 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

static	int	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	// Lock forks
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	// Update last meal time and meals eaten
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	// Simulate eating
	ft_usleep(data->time_to_eat);
	// Unlock forks
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	return (0);
}

/**
 * Philosopher sleeping routine.
 */
static	int	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->someone_died)
		return (1);
	ft_usleep(data->time_to_sleep);
	return (0);	
}

/**
 * Philosopher thinking routine.
 */
static	int	philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->someone_died)
		return (1);
	// Thinking time can be negligible or a small delay
	ft_usleep(50);
	return (0);
}

/**
 * Philosopher routine function.
 * Each philosopher will repeatedly eat, sleep, and think until someone dies.
 */

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (data->someone_died == 0)
	{
		if (philo_eat(philo) != 0)
			break ;
		if (philo_sleep(philo) != 0)
			break ;
		if (philo_think(philo) != 0)
			break ;
	}
	return (NULL);
}