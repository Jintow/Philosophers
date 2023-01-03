/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:43:15 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 22:45:24 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		fork_battle(t_philo_id	*philo, pthread_mutex_t	*fork, int *lock);
void	print_dinner_activity(t_philo_id *philo);

int	eating(t_philo_id *philo)
{
	if (fork_battle(philo, philo->fork1, philo->lock1))
		return (1);
	if (fork_battle(philo, philo->fork2, philo->lock2))
	{
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	print_dinner_activity(philo);
	if (activity_time(philo, philo->time_eat, 'd'))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	*philo->lock1 = 0;
	pthread_mutex_unlock(philo->fork1);
	*philo->lock2 = 0;
	pthread_mutex_unlock(philo->fork2);
	return (0);
}
//A savoir : reactualisation du dernier repas au debut ou a la fin du repas?

int	fork_battle(t_philo_id	*philo, pthread_mutex_t	*fork, int *lock)
{
	int				death_time;
	struct timeval	current;
	int				time_gap;

	while (*lock == 1)
	{
		gettimeofday(&current, NULL);
		death_time = (current.tv_sec - philo->last_meal.tv_sec) * 1000 + \
			(current.tv_usec - philo->last_meal.tv_usec) / 1000;
		if (check_endof_sim(philo, death_time))
			return (1);
		usleep(300);
	}
	pthread_mutex_lock(fork);
	*lock = 1;
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d has taken a fork\n", time_gap, philo->id + 1);
	return (0);
}

void	print_dinner_activity(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
		(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d is eating\n", time_gap, philo->id + 1);
	gettimeofday(&philo->last_meal, NULL);
	philo->nb_meal_taken += 1;
}
