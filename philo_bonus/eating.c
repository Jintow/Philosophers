/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:43:15 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 22:56:24 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		fork_battle(t_philo_id *philo);
int		print_dinner_activity(t_philo_id *philo);

int	eating(t_philo_id *philo)
{
	if (fork_battle(philo))
		return (1);
	if (philo->nb_philo == 1)
		return (1);
	if (fork_battle(philo))
	{
		sem_post(philo->p_for_all->fork);
		return (1);
	}
	if (print_dinner_activity(philo))
		return (1);
	activity_time(philo->time_eat, philo->id);
	sem_post(philo->p_for_all->fork);
	sem_post(philo->p_for_all->fork);
	return (0);
}

int	fork_battle(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	sem_wait(philo->p_for_all->fork);
	sem_wait(philo->p_for_all->print);
	gettimeofday(&current, NULL);
	time_gap = get_time(current, philo->time0_sim);
	printf("%d philosopher %d has taken a fork\n", time_gap, philo->id + 1);
	sem_post(philo->p_for_all->print);
	return (0);
}

int	print_dinner_activity(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	sem_wait(philo->p_for_all->print);
	gettimeofday(&philo->last_meal, NULL);
	gettimeofday(&current, NULL);
	time_gap = get_time(current, philo->time0_sim);
	printf("%d philosopher %d is eating\n", time_gap, philo->id + 1);
	philo->nb_meal_taken += 1;
	if (philo->nb_meal_taken == philo->nb_meal_max)
		sem_post(philo->p_for_all->meal);
	sem_post(philo->p_for_all->print);
	return (0);
}
