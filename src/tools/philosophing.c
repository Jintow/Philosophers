/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:35:46 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 12:21:17 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_philo_id	*philo)
{
	struct timeval	current;
	int				time_gap;

	if (fork_battle(philo, pfilo->fork1))
		return (1);
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->last_meal.tv_usec) / 1000;
	printf("%d philosopher %d has taken a fork\n", time_gap, philo->id + 1);
	if (fork_battle(philo, pfilo->fork2))
		return (1);
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->last_meal.tv_usec) / 1000;
	printf("%d philosopher %d has taken a fork\n", time_gap, philo->id + 1);
	printf("%d philosopher %d has is eating\n", time_gap, philo->id + 1);
	gettimeofday(philo->last_meal);
	philo->nb_meal_taken += 1;
	if (dinner_time(philo))
		return (1);
	return (0);
}

int	fork_battle(t_philo_id	*philo, pthread_mutex_t	fork)
{
	int				fork_status;
	double			death_time;
	struct timeval	current;

	while (1)
	{
		fork_status = pthread_mutex_lock(fork);
		if (fork_status == 0)
			break ;
		else if (fork_status != 16)
			fail_exit2(ERR_LOCK, philo);
		gettimeofday(&current);
		death_time = current.tv_sec - philo->last_meal.tv_sec + \
			(current.tv_usec - philo->last_meal.tv_usec) / 1000000;
		if (death_time >= philo->time_death)
			return (1);
		usleep(5000);
	}
	return (0);
}

int	dinner_time(t_philo_id *philo)
{
	int				dinning;
	double			death_time;
	struct timeval	current;

	dinning = 0;
	while (dinning < philo->time_eat)
	{
		gettimeofday(&current);
		death_time = current.tv_sec - philo->last_meal.tv_sec + \
			(current.tv_usec - philo->last_meal.tv_usec) / 1000000;
		if (check_endof_sim(philo))
			return (1);
		dinning++;
		usleep(1000);
	}
	return (0);
}

int	check_endof_sim(t_philo_id *philo, double death_time)
{
	int		i;
	t_philo	all;

	if (philo->p_for_all->is_dead)
		return (1);
	if (death_time >= philo->time_death)
	{
		philo->p_for_all->is_dead = 1;
		return (1);
	}
	all = philo->p_for_all;
	i = 0;
	if (all->nb_meal >= 0)
	{		
		while (i < all->nb_philo)
		{
			if (all->tab_philo[i].nb_meal_taken < \
				all->tab_philo[i].nb_meal_max)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	living(void *arg)
{
	int			time;
	int			time_to_death;
	t_philo_id	*philo;

	philo = (t_philo_id *)arg;
	gettimeofday(&philo->last_meal);
	while (1)
	{

	}
}

void	philosophing(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_create(&philo->thread[i], NULL, living, \
			&philo->tab_philo[i]) != 0)
			fail_exit2(ERR_THREADS, philo);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(&living, &philo->tab_philo[i], NULL) != 0)
			fail_exit2(ERR_THREADS, philo);
		i++;
	}
}
