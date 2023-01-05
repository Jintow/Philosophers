/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:46:10 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/05 18:45:20 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Central functino for eating and sleeping.
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
	while (duration < time_activity)
	{
		gettimeofday(&current, NULL);
		duration = (current.tv_sec - activity.tv_sec) * 1000 + \
			(current.tv_usec - activity.tv_usec) / 1000;
		usleep(1);
	}
	return (0);
}
