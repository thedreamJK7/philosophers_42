/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:19:13 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/12 18:50:12 by javokhir         ###   ########.fr       */
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

void destroy_fork_mutexes(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}

/**
 * Clean up allocated resources and destroy mutexes.
 */
void	cleanup(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	destroy_single_mutex(&data->print_mutex);
	destroy_fork_mutexes(data, data->num_philos);
}
