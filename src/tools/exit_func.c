/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:52:39 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 13:27:34 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fail_exit(char *msg, char **tab_arg)
{
	(void)tab_arg;
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	fail_exit2(char *msg, t_philo *philo, int nb)
{
	int	i;

	printf("%s", msg);
	i = 0;
	if (philo->fork)
	{
		while (i < nb)
			pthread_mutex_destroy(&philo->fork[i++]);
		free(philo->fork);
	}
	if (philo->thread)
		free(philo->thread);
	if (philo->tab_philo)
		free(philo->tab_philo);
	if (philo->lock)
		free(philo->lock);
	if (philo->bool_print)
		pthread_mutex_destroy(&philo->print);
	exit(EXIT_FAILURE);
}

void	destroy_and_exit(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->print);
	free(philo->thread);
	free(philo->tab_philo);
	free(philo->lock);
	free(philo->fork);
	exit(EXIT_SUCCESS);
}
