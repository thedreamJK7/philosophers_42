/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:19:13 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/14 20:40:39 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/**
 * Destroy a single mutex.
 */
void	destroy_single_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
}

/**
 * Destroy fork mutexes and free allocated resources.
*/
void	destroy_fork_mutexes(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

/**
 * Clean up allocated resources and destroy mutexes.
*/
void	cleanup(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
			i++;
		}
	}
	destroy_single_mutex(&data->print_mutex);
	if (data->forks)
		destroy_fork_mutexes(data, data->num_philos);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
