/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:07:15 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 16:37:56 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Creation of threads and joining.
*/

void	activate_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_create(&philo->thread[i], NULL, &living, \
			&philo->tab_philo[i]) != 0)
			fail_exit2(ERR_THREADS, philo, philo->nb_philo);
		i++;
	}
	while (1)
	{
		if (check_endof_sim(philo))
			break ;
		usleep (2500);
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(philo->thread[i], NULL) != 0)
			fail_exit2(ERR_JOIN, philo, philo->nb_philo);
		i++;
	}
	destroy_and_exit(philo);
}
