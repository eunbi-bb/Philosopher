/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 08:36:14 by eucho         #+#    #+#                 */
/*   Updated: 2023/09/15 08:44:35 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	current;
	long			ms;

	gettimeofday(&current, NULL);
	ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (ms);
}

long	elapsed_time(long start)
{
	long	time;

	time = get_time() - start;
	return (time);
}

void	set_pasta_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->lock);
	philo->last_pasta = get_time();
	pthread_mutex_unlock(&philo->utils->lock);
}

long	last_pasta_time(t_philo *philo)
{
	long	last_pasta_time;

	pthread_mutex_lock(&philo->utils->lock);
	last_pasta_time = philo->last_pasta;
	pthread_mutex_unlock(&philo->utils->lock);
	return (last_pasta_time);
}

void	precise_usleep(long long usec)
{
	struct timeval	start;
	struct timeval	end;
	long			elapsed;

	gettimeofday(&start, NULL);
	usleep(usec);
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) * 1000000 + \
				(end.tv_usec - start.tv_usec);
	if (elapsed < usec)
		usleep(usec - elapsed);
}
