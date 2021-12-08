/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:37:56 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/07 22:32:22 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static t_philo	**prepare_commensals(t_general *g)
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
		philos[i]->t = 0;
		philos[i]->meals = 0;
		philos[i]->start = g->start;
		i++;
	}
	return (philos);
}

void	lay_the_table(t_general *g)
{
	t_philo		**philos;

	philos = prepare_commensals(g);
	meal(philos, g);
}
