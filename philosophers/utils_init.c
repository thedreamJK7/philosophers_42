/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:47:58 by javokhir          #+#    #+#             */
/*   Updated: 2025/11/15 11:38:42 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/*
** Validate command-line arguments before converting them to integers.
** Ensures all arguments are positive integers.
*/

static int	validate_before_atoi(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_number(argv[i]) != 0)
			return (ft_putstr_fd(ERROR_POSITIVE_INT, 2), 1);
		i++;
	}
	return (0);
}

/**
 * Validate command-line arguments count and format.
 */
int	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(INVALID_INPUT_MSG, 2), 1);
	if (validate_before_atoi(argc, argv) != 0)
		return (1);
	return (0);
}

/**
 * Initialize mutexes for forks and printing.
 */
int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_putstr_fd(ERROR_MUTEX_INIT, 2), \
			destroy_fork_mutexes(data, i), 1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ft_putstr_fd(ERROR_MUTEX_INIT, 2), \
		destroy_fork_mutexes(data, i), 1);
	return (0);
}

