/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:04:08 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/19 14:57:56 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> 
# include <sys/time.h>

# define FALSE -1

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[1;34m"
# define PURPLE "\e[0;35m"

typedef struct s_param{
	int	nb_philo;
	int	die;
	int	eat;
	int	sleep;
	int	need_eat;
	int	begin;
}t_param;

typedef struct s_philo{
	int				id;
	int				lst_eat;
	int				alive;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork;
	t_param			*pars;
}t_philo;

t_param	*parsing(int argc, char **argv);
int		init_philo(t_param *philo);
void	init_fork(pthread_mutex_t *fork, int len);
t_philo	*init_lst_eat(t_param *pars, pthread_mutex_t *fork);
void	meal(t_philo *philo);
int		get_time(void);
void	manager(t_philo *philo, t_param *pars);

#endif
