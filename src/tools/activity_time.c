/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:46:10 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 22:46:44 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		usleep(300);
	}
	return (0);
}
