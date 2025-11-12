/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:08:15 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/12 21:52:27 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/**
 * Get the current time in milliseconds.
 */

long long get_time_in_ms()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (-1);
}
/**
 * Sleep for a specified duration in milliseconds.
 */

void ft_sleep(long long duration)
{
	long long start_time = get_time_in_ms();

	while (get_time_in_ms() - start_time < duration)
		usleep(100);
}

/**
 * Print a message with timestamp and philosopher ID.
 */
void print_status(t_data *data, int philo_id, const char *message)
{
	long long timestamp;

	pthread_mutex_lock(&data->print_mutex);
	if (!data->someone_died)
	{
		timestamp = get_time_in_ms() - data->start_time;
		printf("%lld %d %s\n", timestamp, philo_id + 1, message);
	}
	pthread_mutex_unlock(&data->print_mutex);
}
