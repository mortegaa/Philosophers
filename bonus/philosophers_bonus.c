/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:13:01 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/06 19:12:08 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_general	read_arguments(int argc, char **argv)
{
	t_general	g;

	if (argc > 6 || argc < 5)
		exit_mess("No correct number of arguments\n");
	g.n_philos = ft_atoi(argv[1]);
	g.tdie = ft_atoi(argv[2]);
	g.teat = ft_atoi(argv[3]);
	g.tsleep = ft_atoi(argv[4]);
	g.meals = -1;
	if (argc == 6)
	{
		g.meals = ft_atoi(argv[5]);
		if (g.meals < 0)
			exit_mess("No valid parameter value\n");
	}
	if (g.n_philos < 0 || g.meals < 0)
		exit_mess("No valid parameter value");
	else if (g.n_philos == 0)
		exit_mess("There is no commensals :(\n");
	else if (g.meals == 0)
		exit_mess("There is no meal :(\n");
	else if (g.teat < 0 || g.teat < 0 || g.tsleep < 0)
		exit_mess("Time values no valid\n");
	return (g);
}

t_philo	**prepare_commensals(t_general *g)
{
	size_t	i;
	t_philo	**philos;

	philos = (t_philo **)malloc(sizeof(t_philo *) * g->n_philos);
	i = 0;
	while (i < g->n_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->id = i + 1;
		philos[i]->teat = g->teat;
		philos[i]->tsleep = g->tsleep;
		philos[i]->t = 0;
		philos[i]->meals = 0;
		philos[i]->start = g->start;
		i++;
	}
	return (philos);
}

void	prepare_waiter(t_waiter *waiter, t_general*g, t_philo *philo, bool *f)
{
	waiter->n_philos = g->n_philos;
	waiter->tdie = g->tdie;
	waiter->philo = philo;
	waiter->f = f;
	*(waiter->f) = true;
	waiter->start = g->start;
	waiter->meals = g->meals;
}


void	lay_the_table(t_general *g)
{
	t_philo		**philos;

	philos = prepare_commensals(g);
	meal(philos, g);
}

void	*monitoring(void *lks)
{
	t_waiter	*wt;

	wt = (t_waiter *)lks;
	while (*(wt->f) == true)
		;
	while (1)
	{
		if (get_time(wt->start) - wt->philo->t > wt->tdie)
		{
			*(wt->f) = true;
			print_mess(wt->philo->id, "died", wt->start);
			break ;
		}
		else if (wt->meals > 0 && wt->philo->meals == wt->meals)
		{
			*(wt->f) = true;
			break ;
		}
	}
	return (NULL);
}

void	call_philo(t_philo *ph, t_general *g)
{
	t_waiter	waiter;
	bool		f;

	prepare_waiter(&waiter, g, ph, &f);
	ph->f = &f;
	ph->pid = fork();
	if (ph->pid)
		return ;
	else
	{
		pthread_create(&(waiter.thread), NULL, &monitoring, &waiter);
		pthread_create(&(ph->thread), NULL, &routine, ph);
		*(waiter.f) = false;
		pthread_join(waiter.thread, NULL);
		pthread_join(ph->thread, NULL);
		exit(EXIT_SUCCESS);
	}
}

void	*routine(void *lks)
{
	sem_t	*forks;
	t_philo	*ph;

	ph = (t_philo *)lks;
	forks = sem_open("FORKS", O_CREAT, 0660, 4);
	printf("Ph[%02zu] has arrived\n", ph->id);
	while (1)
	{
		sem_wait(forks);
		print_mess(ph->id, "has taken a fork", ph->start);
		sem_wait(forks);
		print_mess(ph->id, "has taken a fork", ph->start);
		ph->t = get_time(ph->start);
		print_mess(ph->id, "is eating", ph->start);
		if (*(ph->f) == true)
			break ;
		usleep(ph->teat * 1000);
		ph->meals++;
		sem_post(forks);
		sem_post(forks);
		print_mess(ph->id, "is sleeping", ph->start);
		usleep(ph->tsleep * 1000);
		print_mess(ph->id, "is thinking", ph->start);
	}
	sem_close(forks);
	return (NULL);
}

void	meal(t_philo **philos, t_general *g)
{
	size_t	i;
	sem_t	*forks;
	pid_t	finish;

	forks = sem_open("FORKS", O_CREAT, 0660, g->n_philos);
	i = 0;
	finish = 0;
	while (i < g->n_philos)
	{
		call_philo(philos[i], g);
		i++;
	}
	// Falta como conseguir saber cuando termina uno de los procesos y Matar al resto
	i = 0;
	while (i < g->n_philos)
	{
		kill(philos[i]->pid, SIGINT);
		i++;
	}
	sem_close(forks);
	sem_unlink("FORKS");
	printf("Comida terminada\n");
}


int	main(int argc, char **argv)
{
	t_general		g;
	struct timeval	start;

	g = read_arguments(argc, argv);
	gettimeofday(&start, NULL);
	g.start = start;
	lay_the_table(&g);
}
