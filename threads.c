#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* routine(void *arg)
{
	long tid = (long)arg;
	printf("Salom men #%ld! - threadman \n", tid);
	pthread_exit(NULL);
}

int main()
{
	pthread_t t[3];
	
	for (long i = 0; 3 >= i; i++)
	{
		pthread_create(&t[i], NULL, routine, (void *)i);
	}
	for (long i = 0; 3 >= i; i++)
	{
		pthread_join(t[i], NULL);
	}
	return (0);
}
