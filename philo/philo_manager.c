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

int	time_to_die(t_philo *philo)
{
	int	time;

	time = get_time();
	if (time - philo->lst_eat > philo->pars->die / 1000)
	{
		philo->alive = FALSE;
		printf("%s%d %d died%s\n", RED, time - philo->pars->begin, philo->id, NC);
		return (1);
	}
	return (0);
}

void	take_stop(t_philo *philo)
{
	int	i;
	int	max;
	
	max = philo->pars->nb_philo;
	i = 0;
	while (i < max)
	{
		philo[i].alive = FALSE;
		printf("philo %d done\n", i);
		i++;
	}
}

void	manager(t_philo *philo, t_param *pars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (1)
	{
		pthread_mutex_lock(&philo[i].lock);
		if (pars->need_eat && philo[i].alive >= philo[i].pars->need_eat)
			count++;
		if (count >= pars->nb_philo || philo[i].alive == FALSE)
		{
			pthread_mutex_unlock(&philo[i].lock);
			break ;
		}
		if (time_to_die(&philo[i]) == 1)
		{
			take_stop(&philo[0]);
			pthread_mutex_unlock(&philo[i].lock);
			break ;
		}
		pthread_mutex_unlock(&philo[i].lock);
		if (i  + 1 >= pars->nb_philo)
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

	time = get_time();
	printf("%s%d %d is eating%s\n", PURPLE, time - philo->pars->begin, philo->id, NC);
	usleep(philo->pars->eat);
	philo->alive++;
	philo->lst_eat = time;
}
