/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:35:46 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/09 12:52:04 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philo_id *philo);
int	thinking(t_philo_id *philo);

/*
	Function for the living of each philosopher.
	First wait the start of all threat.
	Then infinite loop for each thread.
*/
void	*living(void *arg)
{
	t_philo_id		*philo;

	philo = (t_philo_id *)arg;
	pthread_mutex_lock(&philo->p_for_all->print);
	pthread_mutex_unlock(&philo->p_for_all->print);
	gettimeofday(&philo->last_meal, NULL);
	gettimeofday(&philo->time0_sim, NULL);
	if (philo->id % 2 == 0 && philo->nb_philo > 1)
		usleep(30000);
	while (1)
	{
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
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
	time_gap = get_time(current, philo->time0_sim);
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
	time_gap = get_time(current, philo->time0_sim);
	printf("%d philosopher %d is thinking\n", time_gap, philo->id + 1);
	pthread_mutex_unlock(&philo->p_for_all->print);
	return (0);
}
