#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 1;
pthread_mutex_t mutex;

void* routine(void *arg)
{
	for (size_t i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	pthread_t t[10];
	pthread_mutex_init(&mutex, NULL);
	for (size_t i = 0; i < 10; i++)
	{
		printf("Thread %ld has started\n", i + 1);
		if (pthread_create(t + i, NULL, &routine, NULL) != 0)
			return (1);
	}
	for (size_t i = 0; i < 10; i++)
	{
		printf("Thread %ld has finished\n", i + 1);
		if (pthread_join(t[i], NULL) != 0)
			return (2);
	}
	pthread_mutex_destroy(&mutex);
	printf("x = %d\n", x);
	return (0);
}
