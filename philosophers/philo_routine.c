/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:32:06 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/15 11:42:38 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/**
 * Philosopher takes forks (locks mutexes).
 */
static	int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, FORK_TAKEN);
		if (philo->data->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			return (1);
		}
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, FORK_TAKEN);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, FORK_TAKEN);
	}
	return (0);
}

static int	release_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
	}
	return (0);
}

/**
 * Philosopher eating routine.
 */
static	int	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (take_forks(philo) != 0)
		return (1);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	print_action(philo, EATING);
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	release_forks(philo);
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
