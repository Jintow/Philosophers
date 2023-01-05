/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:07:15 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/05 18:47:05 by jlitaudo         ###   ########.fr       */
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
		usleep (2000);
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		// dprintf(2, "%d %d\n", philo->nb_philo, i + 1);
		if (pthread_join(philo->thread[i], NULL) != 0)
			fail_exit2(ERR_JOIN, philo, philo->nb_philo);
		i++;
	}
	destroy_and_exit(philo);
}
