#include "../includes/philo.h"

int	grab_fork(t_philo *philo)
{
	if (philo->index == 0)
		return (philo->utils->n_philo - 1);
	else
		return (philo->index - 1);
}

void	go_eat(t_philo *philo)
{
	int	a_fork;

	a_fork = grab_fork(philo);
	//
	pthread_mutex_lock(&philo->utils->forks[a_fork]);
	lock_msg(philo->utils, elapsed_time(philo->utils->time_set), "grabbed a fork.", philo->index);
	//
	pthread_mutex_lock(&philo->utils->forks[philo->index]);
	lock_msg(philo->utils, elapsed_time(philo->utils->time_set), "grabbed a fork.", philo->index);
	set_pasta_time(philo);
	philo->pasta--;
	lock_msg(philo->utils, elapsed_time(philo->utils->time_set), "is eating spaghetti.", philo->index);
	go_sleep(philo->utils->t_eat);
	pthread_mutex_unlock(&philo->utils->forks[a_fork]);
	pthread_mutex_unlock(&philo->utils->forks[philo->index]);
}

void	go_sleep(int time)
{
	long	start;
	long	elapsed;

	start = retrieve_ms();
	elapsed = 0;
	while (elapsed < time)
	{
		usleep(time * 1000);
		elapsed = retrieve_ms() - start;
	}
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	if (philo->index % 2 == 0)
		usleep(philo->utils->t_eat * 1000);
	while (!check_end(philo->utils) && philo->pasta != 0)
	{
		lock_msg(philo->utils, elapsed_time(philo->utils->time_set), "is thinking.", philo->index);
		go_eat(philo);
		lock_msg(philo->utils, elapsed_time(philo->utils->time_set), "is sleeping.", philo->index);
		go_sleep(philo->utils->t_sleep);
	}
	return (NULL);
}
