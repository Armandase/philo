/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:25:25 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/10 17:50:14 by adamiens         ###   ########.fr       */
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

void	modidfy_counter(int	*i, int *count, int nb_philo)
{
	if ((*i) + 1 >= nb_philo)
	{
		*i = 0;
		*count = 0;
	}
	else
		(*i)++;
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
		{
			pthread_mutex_unlock(&philo->pars->time);
			break ;
		}
		pthread_mutex_unlock(&philo->pars->time);
		if (time_to_die(&philo[i]) == 1 || philo->pars->nb_philo <= 1)
			break ;
		modidfy_counter(&i, &count, pars->nb_philo);
	}
}

void	meal(t_philo *philo)
{
	int	time;

	print_status("is eating", philo);
	protect_sleep(philo, philo->pars->eat);
	pthread_mutex_lock(&philo->pars->time);
	philo->alive = philo->alive + 1;
	time = get_time();
	philo->lst_eat = time;
	pthread_mutex_unlock(&philo->pars->time);
}
