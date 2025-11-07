#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;
pthread_mutex_t mutex;

void *increment()
{
	for (size_t i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int main()
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&t1, NULL, increment, NULL);
	pthread_create(&t2, NULL, increment, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex);
	printf("count = %d \n", count);
	return (0);
}
