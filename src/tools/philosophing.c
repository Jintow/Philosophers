/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:35:46 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 17:52:21 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fork_battle(t_philo_id	*philo, pthread_mutex_t	*fork, int *lock);
int	activity_time(t_philo_id *philo, int time_activity, char c);
int	check_endof_sim(t_philo_id *philo, int death_time);

int	eating(t_philo_id	*philo)
{
	struct timeval	current;
	int				time_gap;

	if (fork_battle(philo, philo->fork1, philo->lock1))
		return (1);
	if (fork_battle(philo, philo->fork2, philo->lock2))
		return (1);
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
		(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d is eating\n", time_gap, philo->id + 1);
	gettimeofday(&philo->last_meal, NULL);
	philo->nb_meal_taken += 1;
	if (activity_time(philo, philo->time_eat, 'd'))
		return (1);
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
		usleep(500);
	}
	pthread_mutex_lock(fork);
	*lock = 1;
	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d has taken a fork\n", time_gap, philo->id + 1);
	return (0);
}

int	activity_time(t_philo_id *philo, int time_activity, char c)
{
	int				duration;
	int				death_time;
	struct timeval	current;
	struct timeval	activity;

	gettimeofday(&activity, NULL);
	duration = 0;
	while (duration < time_activity)
	{
		gettimeofday(&current, NULL);
		if (c == 'd')
			gettimeofday(&philo->last_meal, NULL);
		death_time = (current.tv_sec - philo->last_meal.tv_sec) * 1000 + \
			(current.tv_usec - philo->last_meal.tv_usec) / 1000;
		duration = (current.tv_sec - activity.tv_sec) * 1000 + \
			(current.tv_usec - activity.tv_usec) / 1000;
		if (check_endof_sim(philo, death_time))
			return (1);
		usleep(1000);
	}
	return (0);
}

int	check_endof_sim(t_philo_id *philo, int death_time)
{
	int		i;
	int		time_gap;
	struct timeval current;
	t_philo	*all;

	if (philo->p_for_all->is_dead)
		return (1);
	if (death_time >= philo->time_death)
	{
		philo->p_for_all->is_dead = 1;
		gettimeofday(&current, NULL);
		time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
		printf("%d philosopher %d died\n", time_gap, philo->id + 1);
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
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

// ajouter peut etre un mutex sur is_dead

int	sleeping(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	gettimeofday(&current, NULL);
	time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
			(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
	printf("%d philosopher %d is sleeping\n", time_gap, philo->id + 1);
	if (activity_time(philo, philo->time_sleep, 's'))
		return (1);
	return (0);
}

void	*living(void *arg)
{
	t_philo_id		*philo;
	struct timeval	current;
	int				time_gap;
	int				init;

	philo = (t_philo_id *)arg;
	init = 0;
	while (1)
	{
		if (init == 0 && philo->id % 2 == 0)
			usleep(1000);
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		gettimeofday(&current, NULL);
		time_gap = (current.tv_sec - philo->time0_sim.tv_sec) * 1000 + \
				(current.tv_usec - philo->time0_sim.tv_usec) / 1000;
		printf("%d philosopher %d is thinking\n", time_gap, philo->id + 1);
		init = 1;
	}
	pthread_mutex_unlock(philo->fork1);
	return (NULL);
}

void	activate_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_create(&philo->thread[i], NULL, &living, \
			&philo->tab_philo[i]) != 0)
			fail_exit2(ERR_THREADS, philo);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(philo->thread[i], NULL) != 0)
			fail_exit2(ERR_THREADS, philo);
		i++;
	}
}
