/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:15:14 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/12 14:33:41 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

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
	size_t			teat;
	size_t			tsleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write;
	size_t			t;
	bool			even;
	bool			*f;
	size_t			meals;
	struct timeval	start;
}		t_philo;

typedef struct s_waiter
{
	pthread_t		thread;
	size_t			n_philos;
	t_philo			**philos;
	size_t			tdie;
	bool			*f;
	bool			on;
	size_t			meals;
	bool			*philomeals;
	pthread_mutex_t	*write;
	struct timeval	start;
}		t_waiter;

/*
**	UTILS FUNCTIONS
*/
void	ft_msleep(size_t time);
size_t	get_time(struct timeval start);
void	print_mess(size_t id, char *s,
			struct timeval start, pthread_mutex_t *wr);
void	exit_mess(char *mess);
int		ft_atoi(const char *str);

/*
**	MEAL FUNCTIONS
*/
void	lay_the_table(t_general *g);
void	meal(t_philo **philos, t_waiter *waiter, pthread_mutex_t **forks);

#endif
