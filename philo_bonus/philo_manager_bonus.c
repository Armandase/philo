/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:25:25 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/11 10:05:38 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	meal(t_philo *philo)
{
	int	time;

	print_status("is eating", philo);
	protect_sleep(philo, philo->pars->eat);
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

void	print_die(t_philo *philo)
{
	sem_post(philo->pars->time);
	sem_wait(philo->pars->time);
	print_status("died", philo);
	sem_wait(philo->pars->print);
	sem_post(philo->pars->dead);
	sem_post(philo->pars->time);
}

void	*manager_routine(void *philo_to_cast)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)philo_to_cast;
	while (1)
	{
		usleep(20);
		time = get_time();
		sem_wait(philo->pars->time);
		if (time - philo->lst_eat > philo->pars->die)
		{
			print_die(philo);
			break ;
		}
		if (philo->pars->need_eat && philo->alive >= philo->pars->need_eat)
		{
			sem_post(philo->pars->time);
			break ;
		}
		sem_post(philo->pars->time);
	}
	return (NULL);
}
