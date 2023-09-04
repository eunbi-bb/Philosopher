#include "../includes/philo.h"

void	lock_msg(t_utils *utils, long time, char *str, int index)
{
	pthread_mutex_lock(&utils->status);
	if (utils->end == false)
		printf("%ld Philosopher %i %s\n", time, index, str);
	pthread_mutex_unlock(&utils->status);
}