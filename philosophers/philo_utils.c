/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:32:45 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/15 13:20:31 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/***
 * Create threads for each philosopher.
*/

int	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, 
			philo_routine, &data->philos[i]) != 0)
		{
			ft_putstr_fd("Error: Failed to create philosopher thread\n", 2);
			while (--i >= 0)
			{
				if (pthread_join(data->philos[i].thread, NULL) != 0)
					ft_putstr_fd("Error: Failed to join philosopher thread\n", 2);
			}
			return (cleanup(data), 1);
		}
		i++;
	}
	return (0);
}

/**
 * Philosopher sleeping routine.
 */
int	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (read_someone_died(data) != 0)
		return (1);
	print_action(philo, SLEEPING);
	ft_usleep(data->time_to_sleep);
	return (0);
}

/**
 * Philosopher thinking routine.
 */
int	philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (read_someone_died(data) != 0)
		return (1);
	print_action(philo, THINKING);
	ft_usleep(50);
	return (0);
}


