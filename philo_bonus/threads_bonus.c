/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:41:55 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/11 17:40:25 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	prepare_waiter(t_waiter *waiter, t_general*g, t_philo *philo, bool *f)
{
	waiter->n_philos = g->n_philos;
	waiter->tdie = g->tdie;
	waiter->philo = philo;
	waiter->f = f;
	*(waiter->f) = false;
	waiter->start = g->start;
	waiter->meals = g->meals;
}

void	*monitoring(void *lks)
{
	t_waiter	*wt;
	sem_t		*write;

	wt = (t_waiter *)lks;
	write = sem_open("WRITE", O_CREAT, 0660, 1);
	while (1)
	{
		if (get_time(wt->start) - wt->philo->t > wt->tdie)
		{
			*(wt->f) = true;
			print_mess(wt->philo->id, "died", wt->start, write);
			break ;
		}
		else if (wt->meals > 0 && wt->philo->meals == wt->meals)
		{
			*(wt->f) = true;
			break ;
		}
	}
	sem_close(write);
	return (NULL);
}

void	*routine(void *lks)
{
	sem_t	*forks;
	sem_t	*write;
	t_philo	*ph;

	ph = (t_philo *)lks;
	forks = sem_open("FORKS", O_CREAT, 0660, ph->n_philos);
	write = sem_open("WRITE", O_CREAT, 0660, 1);
	while (1)
	{
		print_mess(ph->id, "is thinking", ph->start, write);
		if (*(ph->f) == true)
			break ;
		sem_wait(forks);
		print_mess(ph->id, "has taken a fork", ph->start, write);
		sem_wait(forks);
		print_mess(ph->id, "has taken a fork", ph->start, write);
		ph->t = get_time(ph->start);
		print_mess(ph->id, "is eating", ph->start, write);
		ft_msleep(ph->teat);
//		usleep(ph->teat * 1000);
		ph->meals++;
		print_mess(ph->id, "is sleeping", ph->start, write);
		sem_post(forks);
		sem_post(forks);
		ft_msleep(ph->tsleep);
//		usleep(ph->tsleep * 1000);
	}
	sem_close(write);
	sem_close(forks);
	return (NULL);
}
