/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 09:52:02 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/04 12:18:08 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (value == 0 && i == 0)
		return (-1);
	return (value);
}

t_param	*parsing(int argc, char **argv)
{
	t_param			*parsing;

	if (!(argc == 5 || argc == 6))
		return (0);
	parsing = malloc(sizeof(t_param));
	parsing->nb_philo = atoi_protect(argv[1]);
	parsing->die = atoi_protect(argv[2]);
	parsing->eat = atoi_protect(argv[3]);
	parsing->sleep = atoi_protect(argv[4]);
	if (argc == 6)
		parsing->need_eat = atoi_protect(argv[5]);
	else
		parsing->need_eat = 0;
	if (parsing->nb_philo == -1 || parsing->die == -1 || parsing->eat
		== -1 || parsing->sleep == -1 || parsing->need_eat == -1)
	{
		free(parsing);
		return (NULL);
	}
	parsing->begin = get_time();
	pthread_mutex_init(&(parsing->dead), NULL);
	pthread_mutex_init(&(parsing->print), NULL);
	pthread_mutex_init(&(parsing->time), NULL);
	parsing->end = 0;
	return (parsing);
}
