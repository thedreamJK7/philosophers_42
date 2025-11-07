#include "philo.h"

void* philo_life(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	printf("Men tug'ildim %d mana shu vaqtda %ld\n", philo->id, philo->start_time);
	return (0);
}

void	create_threads(t_data *data)
{
	for (size_t i = 0; i < data->num_philo; i++)
		pthread_create(&data->philolo[i].thread, NULL, philo_life, &data->philolo[i]);
}

void	join_threads(t_data *data)
{
	for (size_t i = 0; i < data->num_philo; i++)
		pthread_join(data->philolo[i].thread, NULL);
}

long	get_current_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
