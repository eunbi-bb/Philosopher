#include "../includes/philo.h"

int	check_end(t_utils *utils)
{
	int	status;

	pthread_mutex_lock(&utils->status);
	if (utils->end == true)
		status = 1;
	else
		status = 0;
	pthread_mutex_unlock(&utils->status);
	return (status);
}

void	change_end(t_utils *utils)
{
	pthread_mutex_lock(&utils->status);
	utils->end = true;
	pthread_mutex_unlock(&utils->status);
}

void	set_pasta_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->pasta_time);
	philo->last_pasta = retrieve_ms();
	pthread_mutex_lock(&philo->utils->pasta_time);
}

long	last_pasta_time(t_philo *philo)
{
	long	last_pasta_time;

	pthread_mutex_lock(&philo->utils->pasta_time);
	last_pasta_time = philo->last_pasta;
	pthread_mutex_lock(&philo->utils->pasta_time);
	return (last_pasta_time);
}
