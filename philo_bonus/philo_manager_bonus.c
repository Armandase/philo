/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:25:25 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/04 19:05:18 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	time_to_die(t_philo *philo)
{
	int	time;

	time = get_time();
	sem_wait(philo->pars->time);
	if (time - philo->lst_eat > philo->pars->die)
	{
		philo->alive = FALSE;
		sem_post(philo->pars->time);
		print_status("died", philo);
		sem_wait(philo->pars->dead);
		philo->pars->end = 1;
		sem_post(philo->pars->dead);
		return (1);
	}
	sem_post(philo->pars->time);
	return (0);
}

void	manager(t_philo *philo, t_param *pars)
{
	int	i;

	i = 0;
	while (1)
	{
		sem_wait(philo->pars->time);
		if (philo[i].alive == FALSE)// verif si le boolean de sem est false -> false alors kill every process
		{
			sem_post(philo->pars->time);
			break ;
		}
		sem_post(philo->pars->time);
		if (time_to_die(&philo[i]) == 1)
			break ;
		if (i + 1 >= pars->nb_philo)
			i = 0;
		else
			i++;
	}
	return ;
}

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
