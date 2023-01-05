/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:25:25 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/05 14:52:17 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	free_n_quit(t_philo *philo, int *pid)
{
	sem_close(philo->pars->print);
	sem_close(philo->pars->dead);
	sem_close(philo->pars->fork);
	free(pid);
	free(philo);
	exit (1);
}

void	*manager_routine(void *philo_to_cast)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)philo_to_cast;
	while (1)
	{
		usleep(100);
		time = get_time();
		if (time - philo->lst_eat > philo->pars->die)
		{
			print_status("died", philo);
			sem_wait(philo->pars->print);
			sem_post(philo->pars->dead);
		}
	}
}

void	meal(t_philo *philo)
{
	int	time;

	print_status("is eating", philo);
	usleep(philo->pars->eat * 1000);
	philo->alive = philo->alive + 1;
	time = get_time();
	philo->lst_eat = time;
}
