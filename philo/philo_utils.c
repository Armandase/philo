/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:39:50 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/03 17:17:55 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tv;
	struct timezone	tz;
	int				time;

	gettimeofday(&tv, &tz);
	time = tv.tv_usec / 1000 + ((tv.tv_sec % 1000) * 1000);
	return (time);
}

void	print_status(char *action, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->pars->print);
	pthread_mutex_lock(&philo->pars->dead);
	if (philo->pars->end == 1)
	{
		pthread_mutex_unlock(&philo->pars->print);
		pthread_mutex_unlock(&philo->pars->dead);
		return ;
	}
	pthread_mutex_unlock(&philo->pars->dead);
	time = get_time();
	printf("%d %d %s\n", time - philo->pars->begin, philo->id, action);
	pthread_mutex_unlock(&philo->pars->print);
}

int	stop_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->pars->dead);
	if ((philo->pars->need_eat && philo->alive >= philo->pars->need_eat)
		|| philo->pars->end == 1)
	{
		pthread_mutex_unlock(&philo->pars->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->pars->dead);
	return (0);
}
