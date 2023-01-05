/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_algo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:13:34 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/05 18:40:06 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*start_philo(t_philo *philo)
{
	pthread_t	th_manager;

	pthread_create(&th_manager, NULL, &manager_routine, philo);
	pthread_detach(th_manager);
	if (philo->id % 2 == 0)
	{
		print_status("is thinking", philo);
		usleep(philo->pars->eat * 500);
	}
	while (1)
	{
		if (philo->pars->nb_philo <= 1)
		{
			print_status("died", philo);
			return (NULL);
		}
		fork_action(philo);
		print_status("is sleeping", philo);
		usleep(philo->pars->sleep * 1000);
		print_status("is thinking", philo);
		if (philo->pars->need_eat && philo->alive >= philo->pars->need_eat)
			break ;
	}
	return (NULL);
}

void	*wait_n_exit(void	*manager_to_cast)
{
	int			i;
	t_manager	*manager;

	manager = (t_manager *)manager_to_cast;
	i = manager->philo->pars->nb_philo;
	i--;
	while (i >= 0)
	{
		waitpid(manager->pid[i], NULL, 0);
		i--;
	}
	sem_post(manager->philo->pars->dead);
	return (NULL);
}

void	action_manage(t_philo *philo, int *pid)
{
	t_manager	manager;
	pthread_t	th_full_eat;
	int			i;

	manager.philo = philo;
	manager.pid = pid;
	pthread_create(&th_full_eat, NULL, &wait_n_exit, &manager);
	pthread_detach(th_full_eat);
	sem_wait(philo->pars->dead);
	i = 0;
	while (i < philo->pars->nb_philo)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	sem_post(philo->pars->dead);
	usleep(philo->pars->die + 100);
	free_n_quit(philo, pid);
}

void	init_philo(t_param *pars)
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
			free_n_quit(philo, pid);
		else if (pid[i] == 0)
		{
			start_philo(&philo[i]);
			free_n_quit(philo, pid);
		}
		i++;
	}
	action_manage(philo, pid);
}
