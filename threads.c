#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 1;
pthread_mutex_t mutex;

void* routine(void *arg)
{
	for (size_t i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	pthread_t t1, t2, t3, t4;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (3);
	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
		return (3);
	if (pthread_join(t1, NULL) != 0)
		return (2);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	if (pthread_join(t3, NULL) != 0)
		return (2);
	if (pthread_join(t4, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex);
	printf("x = %d\n", x);
	return (0);
}
