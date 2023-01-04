/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_algo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:13:34 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/04 19:31:10 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	fork_action(t_philo *philo)
{
	sem_wait(philo->pars->fork);
	print_status("has taken fork", philo);
	sem_wait(philo->pars->fork);
	print_status("has taken fork", philo);
	meal(philo);
	sem_post(philo->pars->fork);
	sem_post(philo->pars->fork);
}

void	*start_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		print_status("is thinking", philo);
		usleep(philo->pars->eat * 500);
	}
	while (1)
	{
		if (philo->pars->nb_philo <= 1)
			return (NULL);
		fork_action(philo);
		print_status("is sleeping", philo);
		usleep(philo->pars->sleep * 1000);
		print_status("is thinking", philo);
		if (stop_routine(philo) == 1 || philo->alive >= philo->pars->need_eat)
			break ;
	}
	return (NULL);
}

void	quit_init(t_philo *philo, int *pid)
{
	sem_close(philo->pars->print);
	sem_close(philo->pars->dead);
	sem_close(philo->pars->time);
	free(pid);
	free(philo);
	exit (1);
}

int	init_philo(t_param *pars)
{
	t_philo		*philo;
	int			i;
	int			*pid;

	init_fork(pars);
	philo = init_lst_eat(pars);
	pid = malloc(sizeof(int) * pars->nb_philo);
	i = 0;
	while (i < pars->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			quit_init(philo, pid);
		else if (pid[i] == 0)
		{
			start_philo(&philo[i]);
			quit_init(philo, pid);
			exit (0);
		}
		i++;
	}
	//manager(philo, pars);
	i--;
	while (i > 0)
	{
		waitpid(pid[i], NULL, 0);
		i--;
	}
	sem_close(philo->pars->print);
	sem_close(philo->pars->dead);
	sem_close(philo->pars->time);
	free(pid);
	free(philo);
	return (0);
}
