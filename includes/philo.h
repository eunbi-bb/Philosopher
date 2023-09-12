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
# define	ERROR_ALLOC "Memory allocation error.\n"
# define	ERROR_THREAD "Thread initialization error.\n"
# define	ERROR_THREAD_D "pthread_deatch function error.\n"
# define	ERROR_THREAD_j "pthread_join function error.\n"

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	int				n_must_eat;
	long			last_pasta;
	int				left;
	int				right;
	int				count_pasta;
	struct s_utils	*utils;
}				t_philo;

typedef struct s_utils
{
	t_philo			*philos;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	pasta_time;
	bool			finish;
	long			start;
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_must_eat;
}				t_utils;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//monitoring.c
void	monitoring(t_utils *utils);
int		check_status(t_utils *utils);
void	change_finish(t_utils *utils);
//msg.c
int		err_msg(char *str);
void	philo_msg(t_utils *utils, long time, char *str, int id);
//rountine.c
void	*routine(void *tmp);
void	go_eat(t_philo *philo);
//thread.c
int		calloc_threads(t_utils *utils);
int		threads_join(t_utils *utils);
void	destroy_threads(t_utils *utils);
//timne.c
long	get_time(void);
void	set_pasta_time(t_philo *philo);
long	last_pasta_time(t_philo *philo);
long	elapsed_time(long start);
void	precise_usleep(__useconds_t usec);
#endif