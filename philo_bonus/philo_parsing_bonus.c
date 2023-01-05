/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 09:52:02 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/05 11:21:47 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

long long	atoi_protect(char *str)
{
	int			i;
	long long	value;

	i = 0;
	value = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
		if (value > 2147483647)
			return (-1);
	}
	if ((value == 0 && i == 0) || str[i] != '\0')
		return (-1);
	return (value);
}

void	init_semaphore(t_param *parsing)
{
	sem_unlink("/dead");
	parsing->dead = sem_open("/dead", O_CREAT, 0644, 0);
	if (parsing->dead == SEM_FAILED)
		exit (1);
	sem_unlink("/print");
	parsing->print = sem_open("/print", O_CREAT, 0644, 1);
	if (parsing->print == SEM_FAILED)
	{
		sem_close(parsing->dead);
		exit (1);
	}
}

void	parsing(int argc, char **argv, t_param *parsing)
{
	parsing->nb_philo = atoi_protect(argv[1]);
	parsing->die = atoi_protect(argv[2]);
	parsing->eat = atoi_protect(argv[3]);
	parsing->sleep = atoi_protect(argv[4]);
	if (argc == 6)
		parsing->need_eat = atoi_protect(argv[5]);
	else
		parsing->need_eat = 0;
	if (parsing->nb_philo == -1 || parsing->die == -1
		|| parsing->eat == -1 || parsing->sleep == -1
		|| parsing->need_eat == -1 || (argv[5] && atoi_protect(argv[5]) == 0))
		exit (1);
	parsing->begin = get_time();
	init_semaphore(parsing);
	parsing->end = 0;
}
