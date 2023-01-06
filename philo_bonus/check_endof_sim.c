/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_endof_sim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:08:43 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 23:01:54 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_is_dead(void *arg)
{
	t_philo_id		*philo;
	int				death;
	int				time_gap;
	struct timeval	current;

	philo = (t_philo_id *)arg;
	while (1)
	{	
		gettimeofday(&current, NULL);
		death = get_time(current, philo->last_meal);
		if (death >= philo->time_death)
		{		
			time_gap = get_time(current, philo->time0_sim);
			sem_wait(philo->p_for_all->print);
			printf("%d philosopher %d died\n", time_gap, philo->id + 1);
			sem_post(philo->p_for_all->death);
			break ;
		}
		usleep(2000);
	}
	return (NULL);
}
