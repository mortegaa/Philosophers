/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:27:37 by mortega-          #+#    #+#             */
/*   Updated: 2021/12/11 19:02:36 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_msleep(int time)
{
	struct timeval init;

	gettimeofday(&init, NULL);
	while (get_time(init) < time)
		;
}

int	get_time(struct timeval start)
{
	struct timeval	t;
	size_t			tiempo;

	gettimeofday(&t, NULL);
	tiempo = ((t.tv_sec * 1000 - start.tv_sec * 1000)
			+ (t.tv_usec - start.tv_usec) / 1000);
	return (tiempo);
}

void	print_mess(size_t id, char *s, struct timeval start, sem_t *write)
{
	size_t	time;

	time = get_time(start);
	//printf("time = %zu\n", time);
	sem_wait(write);
	printf("%d Ph[%02zu] %s\n", get_time(start), id, s);
	sem_post(write);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	exit_mess(char *mess)
{
	write(1, mess, ft_strlen(mess));
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int	sum;
	int	i;

	i = -1;
	while (str[++i])
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == ' '))
			return (-1);
	while (*str == ' ')
		str++;
	sum = 0;
	while (*str >= '0' && *str <= '9')
		sum = sum * 10 + *str++ - 48;
	return (sum);
}