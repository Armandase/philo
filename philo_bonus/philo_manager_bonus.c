/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:25:25 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/07 12:11:24 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	meal(t_philo *philo)
{
	int	time;

	print_status("is eating", philo);
	usleep(philo->pars->eat * 1000);
	sem_wait(philo->pars->time);
	philo->alive = philo->alive + 1;
	time = get_time();
	philo->lst_eat = time;
	sem_post(philo->pars->time);
}

void	fork_action(t_philo *philo)
{
	sem_wait(philo->pars->fork);
	print_status("has taken a fork", philo);
	sem_wait(philo->pars->fork);
	print_status("has taken a fork", philo);
	meal(philo);
	sem_post(philo->pars->fork);
	sem_post(philo->pars->fork);
}

void	*manager_routine(void *philo_to_cast)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)philo_to_cast;
	while (1)
	{
		usleep(philo->pars->die);
		time = get_time();
		sem_wait(philo->pars->time);
		if (time - philo->lst_eat > philo->pars->die)
		{
			sem_post(philo->pars->time);
			sem_wait(philo->pars->time);
			print_status("died", philo);
			sem_wait(philo->pars->print);
			sem_post(philo->pars->dead);
			sem_post(philo->pars->time);
			break ;
		}
		sem_post(philo->pars->time);
	}
	return (NULL);
}
