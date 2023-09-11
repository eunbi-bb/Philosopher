#include "../includes/philo.h"

void	philo_msg(t_utils *utils, long time, char *str, int id)
{
	pthread_mutex_lock(&utils->lock);
	if (utils->finish == false)
		printf("%ld\tPhilosopher %i %s\n", time, id, str);
	pthread_mutex_unlock(&utils->lock);
}