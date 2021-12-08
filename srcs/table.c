/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:30:22 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/07 22:22:10 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	**prepare_commensals(t_general *g,
		pthread_mutex_t **forks, bool *f, pthread_mutex_t *write)
{
	int		i;
	t_philo	**philos;

	philos = (t_philo **)malloc(sizeof(t_philo *) * g->n_philos);
	i = 0;
	while (i < g->n_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->id = i + 1;
		philos[i]->teat = g->teat;
		philos[i]->tsleep = g->tsleep;
		philos[i]->left_fork = forks[i];
		if (i == g->n_philos - 1)
			philos[i]->right_fork = forks[0];
		else
			philos[i]->right_fork = forks[i + 1];
		philos[i]->t = 0;
		philos[i]->f = f;
		philos[i]->meals = 0;
		philos[i]->start = g->start;
		philos[i]->write = write;
		i++;
	}
	return (philos);
}

static pthread_mutex_t	**prepare_forks(size_t n_philos)
{
	size_t			i;
	pthread_mutex_t	**forks;

	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * n_philos);
	i = 0;
	while (i < n_philos)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (forks);
}

static void	prepare_waiter(t_waiter *waiter,
		t_general*g, t_philo **philos, bool *f)
{
	waiter->n_philos = g->n_philos;
	waiter->tdie = g->tdie;
	waiter->philos = philos;
	waiter->f = f;
	*(waiter->f) = true;
	waiter->start = g->start;
	waiter->meals = g->meals;
}

void	lay_the_table(t_general *g)
{
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	write;
	t_waiter		waiter;
	bool			f;

	forks = prepare_forks(g->n_philos);
	pthread_mutex_init(&write, NULL);
	philos = prepare_commensals(g, forks, &f, &write);
	prepare_waiter(&waiter, g, philos, &f);
	waiter.write = &write;
	meal(philos, &waiter, forks);
}
