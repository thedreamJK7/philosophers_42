#include "philo.h"

void init(t_data *data, int num_philo)
{
	data->philolo = malloc(sizeof(t_philo) * num_philo);
	if (!data->philolo)
	{
		printf("Malloc fail\n");
		return ;
	}
	data->num_philo = num_philo;
	for (size_t i = 0; i < num_philo; i++)
	{
		data->philolo[i].id = i;
		data->philolo[i].state = THINKING;
		usleep(500);
		data->philolo[i].start_time = get_current_time();
	}
}