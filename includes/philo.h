#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

# define	ERROR_ARGC "Invalid quantity of parameters.\n"
# define	ERROR_ARGV "Invalid input provided.\n"
# define	ERROR_MALLOC "Memory allocation error.\n"

typedef struct	s_philo
{
	pthread_t		thread;
	int				index;
	int				pasta;
	long			last_pasta;
	struct s_utils	*utils;
}				t_philo;

typedef struct s_utils
{
	t_philo			*philos;
	pthread_mutex_t	status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	pasta_time;
	bool			end;
	long			time_set;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
}				t_utils;

//error.c
void	err_msg(char *str);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	lock_msg(t_utils *utils, long time, char *str, int index);
long	retrieve_ms(void);
void	*routine(void *tmp);
void	monitoring_wrapper(t_utils *utils);
void	set_pasta_time(t_philo *philo);
long	last_pasta_time(t_philo *philo);
int		check_end(t_utils *utils);
void	change_end(t_utils *utils);
long	elapsed_time(long start);
void	go_eat(t_philo *philo);
void	go_sleep(int time);
int		create_thread(t_utils *utils, int i);
int		calloc_threads(t_utils *utils);
int		create_thread(t_utils *utils, int i);
int		threads_join(t_utils *utils);
#endif