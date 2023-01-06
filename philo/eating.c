/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:43:15 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 21:25:16 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		fork_battle(t_philo_id	*philo, pthread_mutex_t	*fork, int *lock);
int		print_dinner_activity(t_philo_id *philo);

int	eating(t_philo_id *philo)
{
	if (fork_battle(philo, philo->fork1, philo->lock1))
		return (1);
	if (philo->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	if (fork_battle(philo, philo->fork2, philo->lock2))
	{
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	if (print_dinner_activity(philo))
		return (1);
	activity_time(philo->time_eat, philo->id);
	*philo->lock1 = 0;
	pthread_mutex_unlock(philo->fork1);
	*philo->lock2 = 0;
	pthread_mutex_unlock(philo->fork2);
	return (0);
}

int	fork_battle(t_philo_id	*philo, pthread_mutex_t	*fork, int *lock)
{
	struct timeval	current;
	int				time_gap;

	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->p_for_all->print);
	if (philo->p_for_all->end_of_sim)
	{
		pthread_mutex_unlock(fork);
		pthread_mutex_unlock(&philo->p_for_all->print);
		return (1);
	}
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d has taken a fork\n", time_gap, philo->id + 1);
	pthread_mutex_unlock(&philo->p_for_all->print);
	*lock = 1;
	return (0);
}

int	print_dinner_activity(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	pthread_mutex_lock(&philo->p_for_all->print);
	if (philo->p_for_all->end_of_sim)
	{
		pthread_mutex_unlock(&philo->p_for_all->print);
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	gettimeofday(&philo->last_meal, NULL);
	gettimeofday(&current, NULL);
	philo->nb_meal_taken += 1;
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
		(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d is eating\n", time_gap, philo->id + 1);
	pthread_mutex_unlock(&philo->p_for_all->print);
	return (0);
}
