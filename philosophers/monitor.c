/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:56:24 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/14 20:45:05 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/*
 * Monitor routine to check for philosopher deaths.
 */

void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	long long	current_time;

	data = (t_data *)arg;
	while (!data->someone_died)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			current_time = get_time_in_ms();
			if (current_time - data->philos[i].last_meal > data->time_to_die)
			{
				print_action(&data->philos[i], "died");
				data->someone_died = 1;
				pthread_mutex_unlock(&data->philos[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			i++;
		}
	}
	return (NULL);
}
