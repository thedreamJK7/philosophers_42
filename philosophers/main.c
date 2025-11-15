/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:07:43 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/15 18:43:10 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/*
** Main function to start the philosophers simulation.
** It initializes the data, starts the philosopher routines, 
** and cleans up resources.
*/
int	main(int argc, char	**argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (create_philo_threads(&data) != 0)
		return (1);
	if (pthread_create(&data.monitor_routine, NULL, 
			monitor_routine, &data) != 0)
		return (ft_putstr_fd(ERROR_CREATE_MONITOR_T, 2), cleanup(&data), 1);
	if (pthread_join(data.monitor_routine, NULL) != 0)
		ft_putstr_fd(ERROR_JOIN_MONITOR_T, 2);
	if (thread_join_philosophers(&data) != 0)
		return (cleanup(&data), 1);
	return (cleanup(&data), 0);
}
