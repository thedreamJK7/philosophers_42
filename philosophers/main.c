/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:07:43 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/14 21:44:39 by jkubaev          ###   ########.fr       */
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
	if (create_philo_threads(&data) != 0)
		return (1);
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
