#include "../includes/philo.h"

long	retrieve_ms(void)
{
	struct	timeval	current;
	long	ms;

	gettimeofday(&current, NULL);
	ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (ms);
}

long	elapsed_time(long start)
{
	long	time;

	time = retrieve_ms() - start;
	return (time);
}
