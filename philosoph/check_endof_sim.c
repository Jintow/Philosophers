/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_endof_sim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:08:43 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/09 12:41:12 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_endof_sim(t_philo *philo);
int	check_all_meal_taken(t_philo *philo);
int	check_is_dead(t_philo_id *philo);

/*
	Function that check every 2.5 ms if one philo is dead
	or if every philo has taken all his meals.
*/
int	wait_end_of_sim(t_philo *philo)
{
	while (1)
	{
		if (check_endof_sim(philo))
			break ;
		usleep (2500);
	}
	return (1);
}

int	check_endof_sim(t_philo *philo)
{
	int				i;

	pthread_mutex_lock(&philo->print);
	i = 0;
	while (i < philo->nb_philo)
	{
		if (check_is_dead(&philo->tab_philo[i]))
		{
			philo->end_of_sim = 1;
			pthread_mutex_unlock(&philo->print);
			return (1);
		}
		i++;
	}
	if (check_all_meal_taken(philo))
	{
		philo->end_of_sim = 1;
		pthread_mutex_unlock(&philo->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->print);
	return (0);
}

int	check_is_dead(t_philo_id *philo)
{
	int				death;
	int				time_gap;
	struct timeval	current;

	gettimeofday(&current, NULL);
	death = (current.tv_sec - philo->last_meal.tv_sec) * 1000 + \
				(current.tv_usec - philo->last_meal.tv_usec) / 1000;
	if (death >= philo->time_death)
	{		
		time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
		printf("%d philosopher %d died\n", time_gap, philo->id + 1);
		return (1);
	}
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
