/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:13:01 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/04 17:25:53 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_philo	**prepare_commensals(t_general *g, pthread_mutex_t **forks, bool *f, pthread_mutex_t *write)
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

pthread_mutex_t **prepare_forks(size_t n_philos)
{
	size_t	i;
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

void	prepare_waiter(t_waiter *waiter, t_general*g, t_philo **philos, bool *f)
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
	t_philo		**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	write;
	t_waiter	waiter;
	bool		f;

	forks = prepare_forks(g->n_philos);
	philos = prepare_commensals(g, forks, &f, &write);
	prepare_waiter(&waiter, g, philos, &f);
	waiter.write = &write;
	meal(philos, &waiter);
}

void	*monitoring(void *lks)
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
			//exit(EXIT_SUCCESS);
			break ;
		}
		else if (wt->meals > 0 && wt->philos[i]->meals == wt->meals)
		{
			*(wt->f) = true;
			//exit(EXIT_SUCCESS);
			break ;
		}
		i++;
		if (i == wt->n_philos)
			i = 0;
	}
	return (NULL);
}
void	*routine(void *lks)
{
	t_philo	*ph;

	ph = (t_philo *)lks;
	while (*(ph->f) == true)
		;
	printf("Ph[%02zu] has arrived\n", ph->id);
	while (1)
	{
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
		print_mess(ph->id, "is thinking", ph->start, ph->write);
	}
	return (NULL);
}

void	meal(t_philo **philos, t_waiter *waiter)
{
	size_t	i;

	*(waiter->f) = true;
	pthread_create(&(waiter->thread), NULL, &monitoring, waiter);
	i = 0;
	while (i < waiter->n_philos)
	{
		pthread_create(&(philos[i]->thread), NULL, &routine, philos[i]);
		i++;
	}
	*(waiter->f) = false;
	pthread_join(waiter->thread, NULL);
	i = 0;
	while (i < waiter->n_philos)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	printf("Comida terminada\n");
}


int	main(int argc, char **argv)
{
	t_general		g;
	struct timeval		start;

	g = read_arguments(argc, argv);
	gettimeofday(&start, NULL);
	g.start = start;
	lay_the_table(&g);
}
