/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:41:55 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/12 11:49:39 by mortega-         ###   ########.fr       */
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
		if (get_time(wt->start) - wt->philo->t > (int)wt->tdie)
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

void	eating(t_philo *ph, sem_t *forks, sem_t *write)
{
	print_mess(ph->id, "is thinking", ph->start, write);
	if (*(ph->f) == true)
		return ;
	sem_wait(forks);
	if (*(ph->f) == true)
		return ;
	print_mess(ph->id, "has taken a fork", ph->start, write);
	sem_wait(forks);
	ph->t = get_time(ph->start) + 7;
	if (*(ph->f) == true)
		return ;
	print_mess(ph->id, "has taken a fork", ph->start, write);
	if (*(ph->f) == true)
		return ;
	print_mess(ph->id, "is eating", ph->start, write);
	ft_msleep(ph->teat);
	ph->meals++;
	if (*(ph->f) == true)
		return ;
	print_mess(ph->id, "is sleeping", ph->start, write);
	sem_post(forks);
	sem_post(forks);
	ft_msleep(ph->tsleep);
	return ;
}

void	*routine(void *lks)
{
	sem_t	*forks;
	sem_t	*write;
	t_philo	*ph;

	ph = (t_philo *)lks;
	forks = sem_open("FORKS", O_CREAT, 0660, ph->n_philos);
	write = sem_open("WRITE", O_CREAT, 0660, 1);
	while (*(ph->f) == false)
	{
		eating(ph, forks, write);
	}
	sem_close(write);
	sem_close(forks);
	return (NULL);
}
