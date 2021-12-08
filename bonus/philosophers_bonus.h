/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:24:55 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/07 22:29:30 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_general
{
	int				n_philos;
	int				tdie;
	int				teat;
	int				tsleep;
	int				meals;
	struct timeval	start;
}		t_general;

typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	pid_t			pid;
	size_t			teat;
	size_t			tsleep;
	size_t			t;
	bool			*f;
	size_t			meals;
	struct timeval	start;
}		t_philo;

typedef struct s_waiter
{
	pthread_t		thread;
	size_t			n_philos;
	t_philo			*philo;
	size_t			tdie;
	bool			*f;
	size_t			meals;
	struct timeval	start;
}		t_waiter;

/*
**	UTILS FUNCTIONS
*/
size_t	get_time(struct timeval start);
void	print_mess(size_t id, char *s, struct timeval start);
void	exit_mess(char *mess);
int		ft_atoi(const char *str);

/*
**	THREADS FUNCTIONS
*/
void	*routine(void *lks);
void	prepare_waiter(t_waiter *waiter,
			t_general *g, t_philo *philos, bool *f);
void	*monitoring(void *lks);

/*
**	MEAL FUNCTIONS
*/
void	lay_the_table(t_general *g);
void	meal(t_philo **philos, t_general *g);

#endif
