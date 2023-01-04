/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:58:32 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/04 16:47:50 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_lst_eat(t_param *pars)
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
		i++;
	}
	return (philo);
}

void	init_fork(t_param *parsing)
{
	sem_unlink("/fork");
	parsing->fork = sem_open("/fork", O_CREAT, 0644, parsing->nb_philo);
	if (parsing->fork == SEM_FAILED)
	{
		sem_close(parsing->dead);
		sem_close(parsing->time);
		sem_close(parsing->print);
		exit (1);
	}
}
