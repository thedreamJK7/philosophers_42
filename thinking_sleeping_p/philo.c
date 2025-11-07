#include "philo.h"

int main(int argc, char const *argv[])
{
	t_data	data;
	int		num_philo;

	if (argc != 3)
	{
		printf("Wrong arguments recognized, Please try again\n");
		return (1);
	}
	num_philo = atoi(argv[1]);
	if (num_philo <= 0)
	{
		printf("Invalid argument recognized, Please try again");
		return (1);
	}
	init(&data, num_philo);
	create_threads(&data);
	join_threads(&data);
	free(data.philolo);
	return (0);
}
