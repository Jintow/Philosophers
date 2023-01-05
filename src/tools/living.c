/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:35:46 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/05 18:46:09 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philo_id *philo);
int	thinking(t_philo_id *philo);

void	*living(void *arg)
{
	t_philo_id		*philo;

	philo = (t_philo_id *)arg;
	if (philo->id % 2 == 0)
		usleep(2000);
	while (1)
	{
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	// dprintf(2, "%d is dead\n", philo->id + 1);
	return (NULL);
}

int	sleeping(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	pthread_mutex_lock(&philo->p_for_all->print);
	if (philo->p_for_all->end_of_sim)
	{
		pthread_mutex_unlock(&philo->p_for_all->print);
		return (1);
	}
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d is sleeping\n", time_gap, philo->id + 1);
	pthread_mutex_unlock(&philo->p_for_all->print);
	activity_time(philo->time_sleep, philo->id);
	return (0);
}

int	thinking(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	pthread_mutex_lock(&philo->p_for_all->print);
	if (philo->p_for_all->end_of_sim)
	{
		pthread_mutex_unlock(&philo->p_for_all->print);
		return (1);
	}
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d is thinking\n", time_gap, philo->id + 1);
	pthread_mutex_unlock(&philo->p_for_all->print);
	return (0);
}
