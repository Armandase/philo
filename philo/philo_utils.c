/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:39:50 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/10 15:43:57 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

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
		pthread_mutex_unlock(&philo->pars->dead);
		pthread_mutex_unlock(&philo->pars->print);
		return ;
	}
	time = get_time();
	printf("%d %d %s\n", time - philo->pars->begin, philo->id, action);
	pthread_mutex_unlock(&philo->pars->dead);
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

void	protect_sleep(t_philo *philo, int sleep)
{
	int	begin;
	int	waited;
	int	time;

	begin = get_time();
	waited = begin + sleep;
	while (begin < waited)
	{
		usleep(1000);
		time = get_time();
		if (time - philo->lst_eat > philo->pars->die)
			break ;
		begin = get_time();
	}
}
