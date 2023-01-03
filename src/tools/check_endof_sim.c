/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_endof_sim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:08:43 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 22:53:52 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_meal_taken(t_philo *philo);

int	check_endof_sim(t_philo_id *philo, int death_time)
{
	int				time_gap;
	struct timeval	current;

	if (philo->p_for_all->is_dead)
		return (1);
	if (death_time >= philo->time_death)
	{
		philo->p_for_all->is_dead = 1;
		gettimeofday(&current, NULL);
		time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
		printf("%d philosopher %d died\n", time_gap, philo->id + 1);
		return (1);
	}
	if (check_all_meal_taken(philo->p_for_all))
		return (1);
	return (0);
}

int	check_all_meal_taken(t_philo *philo)
{
	int	i;

	if (philo->nb_meal < 0)
		return (0);
	i = 0;
	while (i < philo->nb_philo)
	{
		if (philo->tab_philo[i].nb_meal_taken < \
			philo->tab_philo[i].nb_meal_max)
			return (0);
		i++;
	}
	return (1);
}
