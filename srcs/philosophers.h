#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_general
{
	size_t	n_philos;
	size_t	tdie;
	size_t	teat;
	size_t	tsleep;
	size_t	meals;
	struct timeval	start;
}		t_general;

typedef struct	s_philo
{
	pthread_t	thread;
	size_t		id;
	size_t		teat;
	size_t		tsleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write;
	size_t		t;
	bool		*f;
	size_t		meals;
	struct timeval		start;
}		t_philo;

typedef struct	s_waiter
{
	pthread_t	thread;
	size_t		n_philos;
	t_philo		**philos;
	size_t		tdie;
	bool		*f;
	size_t		meals;
	pthread_mutex_t	*write;
	struct timeval		start;
	
}		t_waiter;

/*
**	UTILS FUNCTIONS
*/
size_t	get_time(struct timeval start);
void	print_mess(size_t id, char *s, struct timeval start, pthread_mutex_t *wr);
void	exit_mess(char *mess);
int	ft_atoi(const char *str);

/*
**	COMMENSALS FUNCTIONS
*/
t_philo	**prepare_commensals(t_general *g, pthread_mutex_t **forks, bool *f, pthread_mutex_t *write);
void	*routine(void *lks);
/*
**	WAITER FUNCTIONS
*/
void	prepare_waiter(t_waiter *waiter, t_general *g, t_philo **philos, bool *f);
void	*monitoring(void *lks);
/*
**	MEAL FUNCTIONS
*/
pthread_mutex_t	**prepare_forks(size_t n_philos);
void	lay_the_table(t_general *g);
void	meal(t_philo **philos, t_waiter *waiter);

#endif
