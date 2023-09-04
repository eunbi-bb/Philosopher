#include "../includes/philo.h"

void	monitoring(t_utils *utils)
{
	int		i;
	long	diff_pasta;

	i = 0;
	while (i < utils->n_philo)
	{
		diff_pasta = retrieve_ms() - last_pasta_time(&utils->philos[i]);
		if (utils->t_die < diff_pasta)
		{
			change_end(utils);
			if (utils->philos[i].pasta != 0)
				printf("%ld Philosopher %d has died\n", elapsed_time(utils->time_set), utils->philos[i].index);
			break ;
		}
		i++;
	}
}

void	monitoring_wrapper(t_utils *utils)
{
	while (!check_end(utils))
	{
		monitoring(utils);
		usleep(1000);
	}
	free(utils->philos);
	free(utils->forks);
}