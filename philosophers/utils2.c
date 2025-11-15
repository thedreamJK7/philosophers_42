/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:08:15 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/15 12:55:30 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/**
 * Get the current time in milliseconds.
*/
long long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (-1);
}

/**
 * Sleep for a specified duration in milliseconds.
 */
void	ft_usleep(long long time_in_ms)
{
	long long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time_in_ms)
		usleep(100);
}

/**
 * Print a message with timestamp and philosopher ID.
 */
static void	print_status(t_data *data, int philo_id, const char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	if (!read_someone_died(data))
	{
		timestamp = get_time_in_ms() - data->start_time;
		printf("%lldms philo %d %s\n", timestamp, philo_id, message);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

void	print_action(t_philo *philo, const char *action)
{
	print_status(philo->data, philo->id, action);
}
