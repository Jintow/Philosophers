/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:35:46 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 22:55:48 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philo_id *philo);
int	thinking(t_philo_id *philo);

void	living(t_philo_id *philo)
{
	pthread_t	checker;

	if (pthread_create(&checker, NULL, &check_is_dead, philo) != 0)
		fail_exit(ERR_THREADS, NULL);
	if (pthread_detach(checker) != 0)
		fail_exit(ERR_DETACH, NULL);
	gettimeofday(&philo->last_meal, NULL);
	if (philo->id % 2 == 0)
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
	return ;
}

int	sleeping(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	sem_wait(philo->p_for_all->print);
	gettimeofday(&current, NULL);
	time_gap = get_time(current, philo->time0_sim);
	printf("%d philosopher %d is sleeping\n", time_gap, philo->id + 1);
	sem_post(philo->p_for_all->print);
	activity_time(philo->time_sleep, philo->id);
	return (0);
}

int	thinking(t_philo_id *philo)
{
	struct timeval	current;
	int				time_gap;

	sem_wait(philo->p_for_all->print);
	gettimeofday(&current, NULL);
	time_gap = get_time(current, philo->time0_sim);
	printf("%d philosopher %d is thinking\n", time_gap, philo->id + 1);
	sem_post(philo->p_for_all->print);
	return (0);
}
