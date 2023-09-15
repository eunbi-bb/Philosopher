/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 08:36:08 by eucho         #+#    #+#                 */
/*   Updated: 2023/09/15 08:43:41 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	calloc_threads(t_utils *utils)
{
	if (pthread_mutex_init(&utils->lock, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&utils->lock, NULL) != 0)
		return (EXIT_FAILURE);
	utils->philos = ft_calloc(utils->n_philo, sizeof(t_philo));
	utils->forks = ft_calloc(utils->n_philo, sizeof(pthread_mutex_t));
	if (utils->forks == NULL)
	{
		free(utils->philos);
		return (EXIT_FAILURE);
	}
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

void	destroy_threads(t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->n_philo)
	{
		pthread_mutex_destroy(&utils->forks[i]);
		i++;
	}
	free(utils->philos);
	free(utils->forks);
	pthread_mutex_destroy(&utils->pasta_time);
	pthread_mutex_destroy(&utils->lock);
}
