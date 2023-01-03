/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:08:47 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/03 17:35:26 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	close_thread(pthread_t *th_philo, t_param *pars)
{
	int	i;

	i = 0;
	while (i < pars->nb_philo)
	{
		pthread_join(th_philo[i], NULL);
		i++;
	}
	return (0);
}

void	*start_philo(void *philo_cast)
{
	t_philo	*philo;

	philo = (t_philo *)philo_cast;
	if (philo->id % 2 == 0)
	{
		print_status("is thinking", philo);
		usleep(5);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->fork[philo->id - 1]);
		print_status("has taken fork", philo);
		if (philo->id == philo->pars->nb_philo)
			pthread_mutex_lock(&philo->fork[0]);
		else
			pthread_mutex_lock(&philo->fork[philo->id]);
		print_status("has taken fork", philo);
		meal(philo);
		if (philo->id == philo->pars->nb_philo)
			pthread_mutex_unlock(&philo->fork[0]);
		else
			pthread_mutex_unlock(&philo->fork[philo->id]);
		pthread_mutex_unlock(&philo->fork[philo->id - 1]);
		print_status("is sleeping", philo);
		usleep(philo->pars->sleep * 1000);
		print_status("is thinking", philo);
		if (stop_routine(philo) == 1)
			break ;
	}
	return (NULL);
}

int	init_philo(t_param *pars)
{
	t_philo			*philo;
	pthread_t		*th_philo;
	int				i;
	pthread_mutex_t	*fork;

	th_philo = malloc(sizeof(pthread_t) * pars->nb_philo);
	fork = malloc(sizeof(pthread_mutex_t) * pars->nb_philo);
	init_fork(fork, pars->nb_philo);
	philo = init_lst_eat(pars, fork);
	i = 0;
	while (i < pars->nb_philo)
	{
		if (pthread_create(&th_philo[i], NULL, &start_philo, (void *)&philo[i])
			!= 0)
			return (1);
		i++;
	}
	manager(philo, pars);
	close_thread(th_philo, pars);
	free(philo);
	free(th_philo);
	free(fork);
	return (0);
}
