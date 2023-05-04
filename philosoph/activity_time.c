/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:46:10 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/09 12:53:31 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Central function for eating and sleeping.
	It simulates a wait to spend the appropriate time for the activity.
*/
int	activity_time(int time_activity, int id)
{
	int				duration;
	struct timeval	current;
	struct timeval	activity;

	(void)id;
	gettimeofday(&activity, NULL);
	duration = 0;
	usleep(time_activity * 1000 / 2);
	while (duration < time_activity * 1000)
	{
		gettimeofday(&current, NULL);
		duration = (current.tv_sec - activity.tv_sec) * 1000000 + \
			(current.tv_usec - activity.tv_usec);
		usleep(250);
	}
	return (0);
}

/*
	Function that calculates the time in ms between two timeval struct.
*/
int	get_time(struct timeval time1, struct timeval time2)
{
	int	time;

	time = (time1.tv_sec - time2.tv_sec) * 1000 + \
			(time1.tv_usec - time2.tv_usec) / 1000;
	return (time);
}
