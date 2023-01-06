/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:46:10 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 23:05:37 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Central function for eating and sleeping.
	It simulates a wait to spend the appropriate time for the activity.
	usleep(335) is for waiting the minimum amount of time 
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

int	get_time(struct timeval time1, struct timeval time2)
{
	int time;

	time = (time1.tv_sec - time2.tv_sec) * 1000 + \
			(time1.tv_usec - time2.tv_usec) / 1000;
	return (time);
}
