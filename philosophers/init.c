/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:12:54 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/14 20:43:09 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/**
** Validate the converted integer values against defined constraints.
*/
static int	validate_requirements(t_data *data)
{
	if (data->num_philos < MIN_PHILO || data->num_philos > MAX_PHILO)
		return (ft_putstr_fd("Error: Number of philosophers must \
			be between 1-200\n", 2), 1);
	if (data->time_to_die < MIN_TIME || data->time_to_die > MAX_TIME)
		return (ft_putstr_fd("Error: time_to_die must be between \
			60-600000 ms\n", 2), 1);
	if (data->num_meals != -1 && (data->num_meals < 1
			|| data->num_meals > MAX_EAT))
		return (ft_putstr_fd("Error: num_meals must be between \
			1-1000\n", 2), 1);
	return (0);
}

/**
** Initialize time-related data from command-line arguments.
*/
static void	init_time_data(t_data *data, char **argv, int argc)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
}

/**
 * Initialize philosopher structures within the data structure.
 * Assumes data->philos is already allocated.
 * (i + 1) % data->num_philos ensures circular assignment of forks.
*/
static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		pthread_mutex_init(&data->philos[i].last_meal_time_mutex, NULL);
		i++;
	}
}

/**
** Initialize the simulation data structure with command-line arguments.
** Returns 0 on success, 1 on failure.
*/
int	init_data(t_data *data, int argc, char **argv)
{
	if (validate_args(argc, argv) != 0)
		return (1);
	init_time_data(data, argv, argc);
	if (validate_requirements(data) != 0)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (ft_putstr_fd("Error: Memory allocation failed\n", 2), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (free(data->philos), 
			ft_putstr_fd("Error: Memory allocation failed\n", 2), 1);
	init_philos(data);
	if (init_forks(data) != 0)
		return (1);
	return (0);
}
