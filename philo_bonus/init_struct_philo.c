/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:53:26 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 23:16:49 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex_and_philo_id(t_philo *philo);
void	init_time_start_sim(t_philo *philo);
void	init_semaphores(t_philo *philo);
void	check_values(t_philo *philo);

void	init_struct_philo(t_philo *philo, char **tab_info)
{
	philo->nb_philo = ft_atoi(tab_info[0]);
	philo->time_death = ft_atoi(tab_info[1]);
	philo->time_eat = ft_atoi(tab_info[2]);
	philo->time_sleep = ft_atoi(tab_info[3]);
	if (tab_info[4])
		philo->nb_meal_max = ft_atoi(tab_info[4]);
	else
		philo->nb_meal_max = -1;
	check_values(philo);
	philo->nb_meal_taken = 0;
	philo->fork_status = 0;
	philo->print_status = 0;
	philo->death_status = 0;
	philo->meal_status = 0;
	philo->tab_philo = malloc(sizeof(t_philo_id) * philo->nb_philo);
	if (!philo->tab_philo)
		fail_exit2(ERR_MALLOC, philo);
	init_mutex_and_philo_id(philo);
	init_time_start_sim(philo);
	init_semaphores(philo);
}

void	check_values(t_philo *philo)
{
	if (philo->nb_philo == 0 || philo->nb_philo > 200)
		fail_exit(ERR_NB_PHILO, NULL);
	if (philo->time_death < 60 || philo->time_eat < 60 || philo->time_eat < 60)
		fail_exit(ERR_ARG_VALUE, NULL);
	if (philo->nb_meal_max == 0)
		exit(EXIT_SUCCESS);
}

void	init_mutex_and_philo_id(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		philo->tab_philo[i].nb_philo = philo->nb_philo;
		philo->tab_philo[i].id = i;
		philo->tab_philo[i].time_death = philo->time_death;
		philo->tab_philo[i].time_eat = philo->time_eat;
		philo->tab_philo[i].time_sleep = philo->time_sleep;
		philo->tab_philo[i].nb_meal_max = philo->nb_meal_max;
		philo->tab_philo[i].nb_meal_taken = 0;
		philo->tab_philo[i].p_for_all = philo;
	}
}

void	init_time_start_sim(t_philo *philo)
{
	int				i;
	struct timeval	time0;

	gettimeofday(&time0, NULL);
	i = -1;
	while (++i < philo->nb_philo)
	{
		philo->tab_philo[i].time0_sim = time0;
		philo->tab_philo[i].last_meal = time0;
	}
}

void	init_semaphores(t_philo *philo)
{
	sem_unlink("PRINT");
	sem_unlink("FORK");
	sem_unlink("DEATH");
	sem_unlink("MEAL");
	philo->fork = sem_open("FORK", O_CREAT | O_TRUNC, 0600, philo->nb_philo);
	if (philo->fork == SEM_FAILED)
		fail_exit2(ERR_INIT_SEM, philo);
	philo->fork_status = 2;
	philo->print = sem_open("PRINT", O_CREAT | O_TRUNC, 0600, 1);
	if (philo->print == SEM_FAILED)
		fail_exit2(ERR_INIT_SEM, philo);
	philo->print_status = 2;
	philo->death = sem_open("DEATH", O_CREAT | O_TRUNC, 0600, 0);
	if (philo->death == SEM_FAILED)
		fail_exit2(ERR_INIT_SEM, philo);
	philo->death_status = 2;
	philo->meal = sem_open("MEAL", O_CREAT | O_TRUNC, 0600, 0);
	if (philo->meal == SEM_FAILED)
		fail_exit2(ERR_INIT_SEM, philo);
	philo->meal_status = 2;
}
