/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:13:01 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/11 17:22:02 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static t_general	read_arguments(int argc, char **argv)
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
	if (g.n_philos < 0)
		exit_mess("No valid parameter value");
	else if (g.n_philos == 0)
		exit_mess("There is no commensals :(\n");
	else if (g.meals == 0)
		exit_mess("There is no meal :(\n");
	else if (g.teat < 0 || g.teat < 0 || g.tsleep < 0)
		exit_mess("Time values no valid\n");
	return (g);
}

int	main(int argc, char **argv)
{
	t_general		g;
	struct timeval	start;

	sem_unlink("FORKS");
	sem_unlink("WRITE");
	g = read_arguments(argc, argv);
	gettimeofday(&start, NULL);
	g.start = start;
	lay_the_table(&g);
}
