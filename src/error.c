#include "../includes/philo.h"

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

void	err_msg(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	exit(1);
}