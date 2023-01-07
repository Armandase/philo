/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:14:44 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/07 09:54:29 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	*pars;

	if (!(argc == 5 || argc == 6))
		return (0);
	pars = parsing(argc, argv);
	if (pars == NULL)
		return (0);
	init_philo(pars);
	free(pars);
	return (0);
}
