/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 08:35:43 by eucho         #+#    #+#                 */
/*   Updated: 2023/09/15 08:42:10 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_status(t_utils *utils)
{
	int	status;

	pthread_mutex_lock(&utils->lock);
	if (utils->finish == true)
		status = true;
	else
		status = false;
	pthread_mutex_unlock(&utils->lock);
	return (status);
}

void	change_finish(t_utils *utils)
{
	pthread_mutex_lock(&utils->lock);
	utils->finish = true;
	pthread_mutex_unlock(&utils->lock);
}

void	monitoring(t_utils *utils)
{
	int		i;
	long	starvation;

	while (check_status(utils) == false)
	{
		i = 0;
		while (i < utils->n_philo)
		{
			starvation = get_time() - last_pasta_time(&utils->philos[i]);
			if (utils->time_die < starvation)
			{
				change_finish(utils);
				if (utils->philos[i].n_must_eat != 0)
				{
					printf("%ld\tPhilosopher %d died.\n", \
							elapsed_time(utils->start), utils->philos[i].id);
				}
				break ;
			}
			i++;
		}
		precise_usleep(1000);
	}
}
