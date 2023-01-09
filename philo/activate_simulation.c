/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:07:15 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/09 12:45:30 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Function that creates threads.
	Then wait for an end simulation condition.
	Then waits for all the threads to finish with pthread_join.
*/
void	activate_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->print);
	while (i < philo->nb_philo)
	{
		if (pthread_create(&philo->thread[i], NULL, &living, \
			&philo->tab_philo[i]) != 0)
			fail_exit2(ERR_THREADS, philo, philo->nb_philo);
		i++;
	}
	pthread_mutex_unlock(&philo->print);
	usleep(10000);
	wait_end_of_sim(philo);
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(philo->thread[i], NULL) != 0)
			fail_exit2(ERR_JOIN, philo, philo->nb_philo);
		i++;
	}
	destroy_and_exit(philo);
}
