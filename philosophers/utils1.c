/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:07:56 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/12 18:52:56 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	ft_putstr_fd(const char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		k;
	int		sum;

	i = 0;
	sum = 0;
	k = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		k *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + (nptr[i] - '0');
		i++;
	}
	return (sum * k);
}

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



