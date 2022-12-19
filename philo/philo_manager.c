/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:25:25 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/19 13:56:20 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_die(t_philo	*philo)
{
	int	time;

	time = get_time();
	if (time - philo->lst_eat >= philo->pars->die)
	{
		philo->alive = FALSE;
		printf("%s%d %d died%s\n", RED, time - philo->pars->begin, philo->id, NC);
		return (1);
	}
	else
		philo->lst_eat = time;
	return (0);
}

void	manager(t_philo *philo, t_param *pars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < pars->nb_philo)
	{
		pthread_mutex_lock(&philo->lock);
		if (pars->eat && philo->alive == pars->need_eat)
			count++;
		pthread_mutex_unlock(&philo->lock);
		if (count >= pars->nb_philo)
			return ;
		if (time_to_die(philo))
			return ;
		i++;
		if (i == pars->nb_philo)
		{
			i = 0;
			count = 0;
		}
	}
}

void	meal(t_philo *philo)
{
	int	time;

	time = get_time();
	printf("%s%d %d is eating%s\n", PURPLE, time - philo->pars->begin, philo->id, NC);
	usleep(philo->pars->eat);
	philo->lst_eat = time;
}
