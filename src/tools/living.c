/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:35:46 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 22:53:23 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philo_id *philo);

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
	return (NULL);
}

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
