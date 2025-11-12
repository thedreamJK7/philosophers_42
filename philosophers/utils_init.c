/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:47:58 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/12 21:09:51 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/**
 * Validate command-line arguments count and format.
 */

int	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Invalid INPUT: 1.number_of_philosophers 2.time_to_die ", STDERR_FILENO);
		ft_putstr_fd("3.time_to_eat 4.time_to_sleep ", STDERR_FILENO);
		ft_putstr_fd("5.[number_of_times_each_philosopher_must_eat]\n", STDERR_FILENO);
		return (1);
	}
	if (validate_before_atoi(argc, argv) != 0)
		return (1);
	return (0);
}

/**
 * Initialize mutexes for forks and printing.
 */

int init_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_putstr_fd("Error: Mutex initialization failed\n", 2), \
			destroy_fork_mutexes(data, i), 1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ft_putstr_fd("Error: Mutex initialization failed\n", 2), \
		destroy_fork_mutexes(data, i), 1);
	return (0);
}