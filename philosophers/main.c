/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:07:43 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/14 19:02:37 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/*
** Main function to start the philosophers simulation.
** It initializes the data, starts the philosopher routines, and cleans up resources.
*/

int	main(int argc, char	**argv)
{
	t_data	data;
	int		i;

	if (init_data(&data, argc, argv) != 0)
		return (1);
	data.someone_died = 0;
	data.start_time = get_time_in_ms();
	// Initialize last_meal to start_time for all philosophers
	i = 0;
	while (i < data.num_philos)
	{
		pthread_mutex_lock(&data.philos[i].meal_mutex);
		data.philos[i].last_meal = data.start_time;
		pthread_mutex_unlock(&data.philos[i].meal_mutex);
		i++;
	}
	i = -1;
	while (++i < data.num_philos)
	{
		if (pthread_create(&data.philos[i].thread, NULL, 
			philo_routine, &data.philos[i]) != 0)
		{
			ft_putstr_fd("Error: Failed to create philosopher thread\n", 2);
			while (--i >= 0)
			{
				if (pthread_join(data.philos[i].thread, NULL) != 0)
					ft_putstr_fd("Error: Failed to join philosopher thread\n", 2);
			}
			return (cleanup(&data), 1);
		}
	}
	if (pthread_create(&data.monitor_routine, NULL, monitor_routine, &data) != 0)
	{
		ft_putstr_fd("Error: Failed to create monitor thread\n", 2);
		return (cleanup(&data), 1);
	}
	if (pthread_join(data.monitor_routine, NULL) != 0)
		ft_putstr_fd("Error: Failed to join monitor thread\n", 2);
	i = -1;
	while (++i < data.num_philos)
	{
		if (pthread_join(data.philos[i].thread, NULL) != 0)
			ft_putstr_fd("Error: Failed to join philosopher thread\n", 2);
	}
	return (cleanup(&data), 0);
}
