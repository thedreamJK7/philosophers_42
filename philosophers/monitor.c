/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:56:24 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/15 16:27:18 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/*
 * Safely read the someone_died flag.
 */
int	read_someone_died(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->someone_died_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->someone_died_mutex);
	return (result);
}

/*
 * Safely read the someone_died flag.
 */
static void	write_someone_died(t_data *data)
{
	pthread_mutex_lock(&data->someone_died_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->someone_died_mutex);
}

/*
 * Check if a philosopher has died.
 */
int	is_died(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->last_meal_time_mutex);
	current_time = get_time_in_ms();
	if (current_time - philo->last_meal > philo->data->time_to_die)
		return (pthread_mutex_unlock(&philo->last_meal_time_mutex), 1);
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	return (0);
}

/*
 * Check if all philosophers have eaten the required number of meals.
 */
int	all_philos_ate(t_data *data)
{
	int	i;
	int	required_meals;

	if (data->num_meals == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		required_meals = data->num_meals;
		if (data->philos[i].meals_eaten < required_meals)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

/*
 * Monitor routine to check for philosopher deaths.
 */
void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	while (!read_someone_died(data))
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (is_died(&data->philos[i]))
				return (print_action(&data->philos[i], DIED),
					write_someone_died(data), NULL);
		}
		if (all_philos_ate(data))
			return (write_someone_died(data), NULL);
		usleep(1000);
	}
	return (NULL);
}
