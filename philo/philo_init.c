/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:58:32 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/19 15:04:02 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_lst_eat(t_param *pars, pthread_mutex_t *fork)
{
	t_philo			*philo;
	int				time;
	int				i;

	philo = malloc(sizeof(t_philo) * pars->nb_philo);
	i = 0;
	time = get_time();
	while (i < pars->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].lst_eat = time;
		philo[i].alive = 0;
		philo[i].pars = pars;
		philo[i].fork = fork;
		pthread_mutex_init(&(philo[i].lock), NULL);
		i++;
	}
	return (philo);
}

void	init_fork(pthread_mutex_t *fork, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}
