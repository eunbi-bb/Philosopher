#include "../includes/philo.h"

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->forks[philo->left]);
	philo_msg(philo->utils, elapsed_time(philo->utils->start), "grabbed a fork from left.", philo->id);
	pthread_mutex_lock(&philo->utils->forks[philo->right]);
	philo_msg(philo->utils, elapsed_time(philo->utils->start), "grabbed a fork from right.", philo->id);
	philo_msg(philo->utils, elapsed_time(philo->utils->start), "is eating spaghetti.", philo->id);
	set_pasta_time(philo);
	philo->n_must_eat--;
	precise_usleep(philo->utils->time_eat * 1000);
	pthread_mutex_unlock(&philo->utils->forks[philo->right]);
	pthread_mutex_unlock(&philo->utils->forks[philo->left]);
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	if (philo->id % 2 == 0)
		precise_usleep(philo->utils->time_eat * 1000);
	while (!check_status(philo->utils) && philo->n_must_eat != 0)
	{
		go_eat(philo);
		philo_msg(philo->utils, elapsed_time(philo->utils->start), "is sleeping.", philo->id);
		precise_usleep(philo->utils->time_sleep * 1000);
		philo_msg(philo->utils, elapsed_time(philo->utils->start), "is thinking.", philo->id);
	}
	return (NULL);
}
