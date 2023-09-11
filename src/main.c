#include "../includes/philo.h"

int	init_philo(t_utils *utils, int i)
{
	utils->philos[i].id = i + 1;
	utils->philos[i].utils = utils;
	utils->philos[i].n_must_eat = utils->n_must_eat;
	utils->philos[i].last_pasta = get_time();
	utils->philos[i].left = i;
	utils->philos[i].right = (i + 1) % utils->n_philo;
	utils->philos[i].count_pasta = 0;
	if (pthread_create(&utils->philos[i].thread, NULL, &routine, &utils->philos[i]) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_utils(t_utils *utils)
{
	int	i;

	i = 0;
	if (calloc_threads(utils) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	while (i < utils->n_philo)
	{
		if (pthread_mutex_init(&utils->forks[i], NULL) == EXIT_FAILURE)
		{
			free(utils->philos);
			free(utils->forks);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < utils->n_philo)
	{
		if (init_philo(utils, i) == EXIT_FAILURE)
		{
			free(utils->philos);
			free(utils->forks);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parsing(int argc, char **argv, t_utils *utils)
{
	utils->start = get_time();
	utils->finish = false;
	utils->n_philo = ft_atoi(argv[1]);
	utils->time_die = ft_atoi(argv[2]);
	utils->time_eat = ft_atoi(argv[3]);
	utils->time_sleep = ft_atoi(argv[4]);
	utils->n_must_eat = -1;
	if (utils->n_philo < 1)
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		utils->n_must_eat = ft_atoi(argv[5]);
		if (utils->n_must_eat == 0)
			return (EXIT_FAILURE);
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

void	precise_usleep(__useconds_t usec)
{
	struct timeval	start;
	struct timeval	end;
	long			elapsed;

	gettimeofday(&start, NULL);
	usleep(usec);
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	if (elapsed < usec)
		usleep(usec - elapsed);
}

int	check_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (err_msg(ERROR_ARGC));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (err_msg(ERROR_ARGV));
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (err_msg(ERROR_ARGV));
	}
	return(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_utils	utils;

	if (check_input(argc, argv) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	if (parsing(argc, argv, &utils) == EXIT_FAILURE)
		return(err_msg(ERROR_ARGV));
	if (init_utils(&utils) == EXIT_FAILURE)
		return(err_msg(ERROR_ALLOC));
	monitoring(&utils);
	if (utils.n_philo == 1)
		pthread_detach(utils.philos[0].thread);
	else
		threads_join(&utils);
	destroy_threads(&utils);
	return (0);
}