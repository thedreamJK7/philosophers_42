#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

long get_current_time()
{
	struct timeval tv;
	struct tm *tm_info;
	
	gettimeofday(&tv, NULL);
	tm_info = localtime(&tv.tv_sec);
	printf("Hour: %d\n", tm_info->tm_hour);
	printf("Minutes: %d\n", tm_info->tm_min);
	printf("Hour: %d\n", tm_info->tm_sec);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int main()
{
	while (1)
	{
		get_current_time();
		usleep(1000);
	}
	
	printf("Time: %ld\n", get_current_time());
	return 0;
}
