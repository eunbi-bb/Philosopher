#include "../includes/philo.h"

int	init_philo(t_utils *utils, int i)
{
	utils->philos[i].id = i + 1;
	utils->philos[i].utils = utils;
	utils->philos[i].n_must_eat = utils->n_must_eat;
	utils->philos[i].last_pasta = get_time();
	utils->philos[i].left = i;
	utils->philos[i].right = (i + 1) % utils->n_philo;
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

int	main(int argc, char **argv)
{
	t_utils	utils;
	int		tmp_argc;
	char	**tmp_argv;

	if (argc != 5 && argc != 6)
		err_msg(ERROR_ARGC);
	tmp_argc = argc;
	tmp_argv = argv;
	if (parsing(tmp_argc, tmp_argv, &utils) == EXIT_FAILURE)
		err_msg(ERROR_ARGV);
	// if (utils.n_philo == 1)
	// 	return (one_philo(&utils));
	if (init_utils(&utils) == EXIT_FAILURE)
		err_msg(ERROR_MALLOC);
	monitoring(&utils);
	if (utils.n_philo == 1)
		pthread_detach(utils.philos[0].thread);
	else
		threads_join(&utils);

	destroy_threads(&utils);
	return (0);
}