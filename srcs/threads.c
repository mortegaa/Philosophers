/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:31:46 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/07 21:34:13 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*monitoring(void *lks)
{
	size_t		i;
	t_waiter	*wt;

	wt = (t_waiter *)lks;
	while (*(wt->f) == true)
		;
	i = 0;
	while (i < wt->n_philos)
	{
		if (get_time(wt->start) - wt->philos[i]->t > wt->tdie)
		{
			*(wt->f) = true;
			print_mess(wt->philos[i]->id, "died", wt->start, wt->write);
			break ;
		}
		else if (wt->meals > 0 && wt->philos[i]->meals == wt->meals)
		{
			*(wt->f) = true;
			break ;
		}
		i++;
		if (i == wt->n_philos)
			i = 0;
	}
	return (NULL);
}

static void	*routine(void *lks)
{
	t_philo	*ph;

	ph = (t_philo *)lks;
	while (1)
	{	
		print_mess(ph->id, "is thinking", ph->start, ph->write);
		if (*(ph->f) == true)
			break ;
		pthread_mutex_lock(ph->left_fork);
		print_mess(ph->id, "has taken a fork", ph->start, ph->write);
		pthread_mutex_lock(ph->right_fork);
		print_mess(ph->id, "has taken a fork", ph->start, ph->write);
		ph->t = get_time(ph->start);
		print_mess(ph->id, "is eating", ph->start, ph->write);
		usleep(ph->teat * 1000);
		ph->meals++;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		print_mess(ph->id, "is sleeping", ph->start, ph->write);
		usleep(ph->tsleep * 1000);
	}
	return (NULL);
}

void	meal(t_philo **philos, t_waiter *waiter, pthread_mutex_t **forks)
{
	size_t	i;

	i = 0;
	while (i < waiter->n_philos)
	{
		pthread_create(&(philos[i]->thread), NULL, &routine, philos[i]);
		i++;
	}
	pthread_create(&(waiter->thread), NULL, &monitoring, waiter);
	*(waiter->f) = false;
	pthread_join(waiter->thread, NULL);
	i = 0;
	while (i < waiter->n_philos)
	{
		pthread_join(philos[i]->thread, NULL);
		pthread_mutex_destroy(forks[i]);
		i++;
	}
	printf("Meal finished\n");
}

