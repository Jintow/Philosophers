/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:52:39 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/09 12:41:05 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Exit function before a dynamically allocated aray.
*/
void	fail_exit(char *msg, char **tab_arg)
{
	(void)tab_arg;
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

/*
	Exit function for a failure after a dynamically allocated aray and
	initilized mutexes.
*/
void	fail_exit2(char *msg, t_philo *philo, int nb)
{
	int	i;

	printf("%s", msg);
	i = 0;
	if (philo->fork)
	{
		while (i < nb)
			if (pthread_mutex_destroy(&philo->fork[i++]))
				printf(ERR_DESTR);
		free(philo->fork);
	}
	if (philo->thread)
		free(philo->thread);
	if (philo->tab_philo)
		free(philo->tab_philo);
	if (philo->lock)
		free(philo->lock);
	if (philo->bool_print)
		if (pthread_mutex_destroy(&philo->print))
			printf(ERR_DESTR);
	exit(EXIT_FAILURE);
}

/*
	Exit Success function. Free arrays and destroy mutexes.
*/
void	destroy_and_exit(t_philo *philo)
{
	int	i;

	i = philo->nb_philo - 1;
	while (i >= 0)
	{
		if (pthread_mutex_destroy(&philo->fork[i]) != 0)
			fail_exit2(ERR_DESTR, philo, i);
		i--;
	}
	if (pthread_mutex_destroy(&philo->print) != 0)
		fail_exit2(ERR_DESTR, philo, 0);
	free(philo->thread);
	free(philo->tab_philo);
	free(philo->lock);
	free(philo->fork);
	exit(EXIT_SUCCESS);
}
