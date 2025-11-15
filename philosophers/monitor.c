/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:56:24 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/15 13:56:08 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

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
 * Monitor routine to check for philosopher deaths.
 */
void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	long long	current_time;

	data = (t_data *)arg;
	while (!read_someone_died(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			current_time = get_time_in_ms();
			if (current_time - data->philos[i].last_meal > data->time_to_die)
			{
				print_action(&data->philos[i], DIED);
				write_someone_died(data);
				pthread_mutex_unlock(&data->philos[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			i++;
		}
	}
	return (NULL);
}
