#include "../includes/philo.h"

void	philo_msg(t_utils *utils, long time, char *str, int id)
{
	pthread_mutex_lock(&utils->lock);
	if (utils->finish == false)
		printf("%ld\tPhilosopher %i %s\n", time, id, str);
	pthread_mutex_unlock(&utils->lock);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	err_msg(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (EXIT_FAILURE);
}