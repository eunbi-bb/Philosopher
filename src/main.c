#include "../includes/philo.h"

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
		if (create_thread(utils, i) == EXIT_FAILURE)
		{
			free(utils->philos);
			free(utils->forks);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_param(char **argv, t_utils *utils)
{
	utils->n_philo = ft_atoi(argv[0]);
	utils->t_die = ft_atoi(argv[1]);
	utils->t_eat = ft_atoi(argv[2]);
	utils->t_sleep = ft_atoi(argv[3]);
	utils->n_eat = -1;
}

int	parsing(int argc, char **argv, t_utils *utils)
{
	utils->time_set = retrieve_ms();
	utils->end = false;
	if (argv[0] < 1)
		return (EXIT_FAILURE);
	init_param(argv, utils);
	if (argc == 5)
	{
		utils->n_eat = ft_atoi(argv[4]);
		if (utils->n_eat == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
	if (parsing(tmp_argc - 1, ++tmp_argv, &utils) == EXIT_FAILURE)
		err_msg(ERROR_ARGV);
	if (init_utils(&utils) == EXIT_FAILURE)
		err_msg(ERROR_MALLOC);
	monitoring_wrapper(&utils);
	threads_join(&utils);
	return (0);
}