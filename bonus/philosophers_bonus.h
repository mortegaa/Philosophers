#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>

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
	pid_t		pid;
	size_t		teat;
	size_t		tsleep;
	size_t		t;
	bool		*f;
	size_t		meals;
	struct timeval		start;
}		t_philo;

typedef struct	s_waiter
{
	pthread_t	thread;
	size_t		n_philos;
	t_philo		*philo;
	size_t		tdie;
	bool		*f;
	size_t		meals;
	struct timeval		start;
	
}		t_waiter;

/*
**	UTILS FUNCTIONS
*/
size_t	get_time(struct timeval start);
void	print_mess(size_t id, char *s, struct timeval start);
void	exit_mess(char *mess);
int	ft_atoi(const char *str);

/*
**	COMMENSALS FUNCTIONS
*/
t_philo	**prepare_commensals(t_general *g);
void	*routine(void *lks);
/*
**	WAITER FUNCTIONS
*/
void	prepare_waiter(t_waiter *waiter, t_general *g, t_philo *philos, bool *f);
void	*monitoring(void *lks);
/*
**	MEAL FUNCTIONS
*/
pthread_mutex_t	**prepare_forks(size_t n_philos);
void	lay_the_table(t_general *g);
void	meal(t_philo **philos, t_general *g);

#endif
