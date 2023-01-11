/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:01:01 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/11 10:00:58 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>

# define FALSE -1

typedef struct s_param{
	int			nb_philo;
	long int	die;
	long int	eat;
	long int	sleep;
	int			need_eat;
	int			begin;
	int			end;
	sem_t		*print;
	sem_t		*dead;
	sem_t		*time;
	sem_t		*fork;
}t_param;

typedef struct s_philo{
	int				id;
	int				lst_eat;
	int				alive;
	t_param			*pars;
}t_philo;

typedef struct s_manager{
	t_philo	*philo;
	int		*pid;
}t_manager;

void	parsing(int argc, char **argv, t_param *parsing);
t_philo	*init_lst_eat(t_param *pars);
void	init_fork(t_param *parsing);
void	init_philo(t_param *pars);
int		get_time(void);
void	print_status(char *action, t_philo *philo);
int		stop_routine(t_philo *philo);
void	meal(t_philo *philo);
void	*manager_routine(void *philo_to_cast);
void	free_n_quit(t_philo *philo, int *pid);
void	fork_action(t_philo *philo);
void	protect_sleep(t_philo *philo, int sleep);

#endif
