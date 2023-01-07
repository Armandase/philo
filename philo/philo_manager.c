/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:25:25 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/07 12:01:02 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_die(t_philo *philo)
{
	int	time;

	time = get_time();
	pthread_mutex_lock(&philo->pars->time);
	if (time - philo->lst_eat > philo->pars->die)
	{
		philo->alive = FALSE;
		pthread_mutex_unlock(&philo->pars->time);
		print_status("died", philo);
		pthread_mutex_lock(&philo->pars->dead);
		philo->pars->end = 1;
		pthread_mutex_unlock(&philo->pars->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->pars->time);
	return (0);
}

void	manager(t_philo *philo, t_param *pars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(&philo->pars->time);
		if (pars->need_eat && philo[i].alive >= pars->need_eat)
			count++;
		if (count >= pars->nb_philo || philo[i].alive == FALSE)
			break ;
		pthread_mutex_unlock(&philo->pars->time);
		if (time_to_die(&philo[i]) == 1 || philo->pars->nb_philo <= 1)
			break ;
		if (i + 1 >= pars->nb_philo)
		{
			i = 0;
			count = 0;
		}
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
	pthread_mutex_lock(&philo->pars->time);
	philo->alive = philo->alive + 1;
	time = get_time();
	philo->lst_eat = time;
	pthread_mutex_unlock(&philo->pars->time);
}
