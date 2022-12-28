/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:52:39 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/28 16:38:46 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fail_exit(char *msg, char **tab_arg)
{
	ft_dprintf(2, "%s", msg);
	ft_free_tab(tab_arg);
	exit(EXIT_FAILURE);
}

void	fail_exit2(char *msg, t_philo *philo)
{
	int	i;

	ft_dprintf(2, "%s", msg);
	i = 0;
	if (philo->fork)
	{
		while (philo->fork[i])
			pthread_mutex_destroy(philo->fork[i++]);
		free(philo->fork);
	}
	if (philo->thread)
		free(philo->thread);
	if (philo->tab_philo)
		free(philo->tab_philo);
	exit(EXIT_FAILURE);
}
