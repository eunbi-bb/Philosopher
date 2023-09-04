#include "../includes/philo.h"

int	calloc_threads(t_utils *utils)
{
	if (pthread_mutex_init(&utils->status, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&utils->pasta_time, NULL) != 0)
		return (EXIT_FAILURE);
	utils->philos = ft_calloc(utils->n_philo, sizeof(t_philo));
	utils->forks = ft_calloc(utils->n_philo, sizeof(pthread_mutex_t));
	if (utils->forks == NULL)
	{
		free(utils->philos);
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	create_thread(t_utils *utils, int i)
{
	utils->philos[i].index = i;
	utils->philos[i].utils = utils;
	utils->philos[i].pasta = utils->n_eat;
	utils->philos[i].last_pasta = retrieve_ms();
	if (pthread_create(&utils->philos[i].thread, NULL, &routine, &utils->philos[i]) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	threads_join(t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->n_philo)
	{
		if (pthread_join(utils->philos[i].thread, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
