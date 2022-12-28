/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:53:26 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/28 16:40:45 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex_and_philo_id(t_philo *philo);

void	init_struct_philo(t_philo *philo, char **tab_info)
{
	philo->nb_philo = ft_atoi(tab_info[0]);
	philo->time_death = ft_atoi(tab_info[1]);
	philo->time_eat = ft_atoi(tab_info[2]);
	philo->time_sleep = ft_atoi(tab_info[3]);
	if (tab_info[4])
		philo->nb_meal = ft_atoi(tab_info[4]);
	else
		philo->nb_meal = -1;
	ft_free_tab(tab_info);
	philo->thread = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!philo->thread)
		fail_exit2(ERR_MALLOC, philo);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->fork)
		fail_exit2(ERR_MALLOC, philo);
	philo->tab_philo = malloc(sizeof(t_philo_id) * philo->nb_philo);
	if (!philo->tab_philo)
		fail_exit2(ERR_MALLOC, philo);
	init_mutex_and_philo_id(philo);
}

void	init_mutex_and_philo_id(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			fail_exit2(ERR_INIT_MUTEX, philo);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		philo->tab_philo[i].nb_philo = philo->nb_philo;
		philo->tab_philo[i].id = i;
		philo->tab_philo[i].time_death = philo->time_death;
		philo->tab_philo[i].time_eat = philo->time_eat;
		philo->tab_philo[i].time_sleep = philo->time_sleep;
		philo->tab_philo[i].nb_meal = philo->nb_meal;
		philo->tab_philo[i].fork = philo->fork;
		i++;
	}
}
