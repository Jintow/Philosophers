/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:46:10 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/05 09:36:16 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Central functino for eating and sleeping.
	It simulates a wait to spend the appropriate time for the activity.
	usleep(335) is for waiting the minimum amount of time 
*/

int	activity_time(t_philo_id *philo, int time_activity)
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
		death_time = (current.tv_sec - philo->last_meal.tv_sec) * 1000000 + \
			(current.tv_usec - philo->last_meal.tv_usec);
		duration = (current.tv_sec - activity.tv_sec) * 1000000 + \
			(current.tv_usec - activity.tv_usec);
		if (check_endof_sim(philo, death_time))
			return (1);
		usleep(1);
	}
	return (0);
}
