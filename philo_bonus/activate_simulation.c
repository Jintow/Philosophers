/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:07:15 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 23:25:56 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	follow_simulation(t_philo *philo);
void	*check_all_meal_taken(void	*arg);

void	activate_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		philo->tab_philo[i].pid = fork();
		if (philo->tab_philo[i].pid == -1)
			fail_exit2(ERR_FORK, philo);
		else if (philo->tab_philo[i].pid == 0)
			living(&philo->tab_philo[i]);
		i++;
	}
	follow_simulation(philo);
}

void	follow_simulation(t_philo *philo)
{
	pthread_t	checker;
	int			i;

	if (pthread_create(&checker, NULL, &check_all_meal_taken, philo) != 0)
		fail_exit(ERR_THREADS, NULL);
	if (pthread_detach(checker) != 0)
		fail_exit(ERR_DETACH, NULL);
	sem_wait(philo->death);
	i = 0;
	while (i < philo->nb_philo)
	{
		kill(philo->tab_philo[i].pid, SIGKILL);
		sem_post(philo->meal);
		i++;
	}
	destroy_and_exit_parent(philo);
}

void	*check_all_meal_taken(void	*arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->nb_philo)
	{
		sem_wait(philo->meal);
		i++;
	}
	sem_post(philo->death);
	return (NULL);
}
