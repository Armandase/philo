/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:14:44 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/04 17:45:11 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_param	pars;

	if (!(argc == 5 || argc == 6))
		return (0);
	parsing(argc, argv, &pars);
	init_philo(&pars);
	return (0);
}
