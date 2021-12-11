/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:40:12 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/11 17:35:08 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	call_philo(t_philo *ph, t_general *g)
{
	t_waiter	waiter;
	bool		f;

	ph->pid = fork();
	if (!ph->pid)
	{
		prepare_waiter(&waiter, g, ph, &f);
		ph->f = &f;
		pthread_create(&(ph->thread), NULL, &routine, ph);
		pthread_detach(ph->thread);
		pthread_create(&(waiter.thread), NULL, &monitoring, &waiter);
		pthread_join(waiter.thread, NULL);
		pthread_join(ph->thread, NULL);
		exit(EXIT_SUCCESS);
	}
}

void	meal(t_philo **philos, t_general *g)
{
	int		i;

	i = 0;
	while (i < g->n_philos)
	{
		call_philo(philos[i], g);
		usleep(10);
		i++;
	}
	waitpid(0, NULL, 0);
	i = 0;
	while (i < g->n_philos)
	{
		kill(philos[i]->pid, SIGKILL);
		i++;
	}
	sem_unlink("WRITE");
	sem_unlink("FORKS");
	printf("Meal finished\n");
}
