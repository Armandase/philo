/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:39:50 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/05 11:19:58 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

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

	sem_wait(philo->pars->print);
	time = get_time();
	printf("%d %d %s\n", time - philo->pars->begin, philo->id, action);
	sem_post(philo->pars->print);
}
