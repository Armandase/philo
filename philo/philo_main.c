/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:14:44 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/17 10:30:01 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	*pars;

	pars = parsing(argc, argv);
	if (pars == NULL)
		return (0);
	init_philo(pars);
	free(pars);
	return (0);
}
