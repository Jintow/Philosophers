/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:52:39 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 23:24:35 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fail_exit(char *msg, char **tab_arg)
{
	(void)tab_arg;
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	fail_exit2(char *msg, t_philo *philo)
{
	printf("%s", msg);
	if (philo->tab_philo)
		free(philo->tab_philo);
	if (philo->fork_status == 2 && sem_close(philo->fork))
		printf(ERR_SEM_CLOSE);
	if (philo->print_status == 2 && sem_close(philo->print))
		printf(ERR_SEM_CLOSE);
	if (philo->death_status == 2 && sem_close(philo->death))
		printf(ERR_SEM_CLOSE);
	if (philo->meal_status == 2 && sem_close(philo->death))
		printf(ERR_SEM_CLOSE);
	philo->death_status = 1;
	philo->fork_status = 1;
	philo->print_status = 1;
	philo->meal_status = 1;
	if (philo->fork_status == 1 && sem_unlink("FORK"))
		printf(ERR_SEM_UNLINK);
	if (philo->print_status == 1 && sem_unlink("PRINT"))
		printf(ERR_SEM_UNLINK);
	if (philo->death_status == 1 && sem_unlink("END"))
		printf(ERR_SEM_UNLINK);
	if (philo->meal_status == 1 && sem_unlink("MEAL"))
		printf(ERR_SEM_UNLINK);
	exit(EXIT_FAILURE);
}


void	destroy_and_exit_parent(t_philo *philo)
{
	if (sem_close(philo->fork))
		fail_exit2(ERR_SEM_CLOSE, philo);
	philo->fork_status = 1;
	if (sem_close(philo->print))
		fail_exit2(ERR_SEM_CLOSE, philo);
	philo->print_status = 1;
	if (sem_close(philo->death))
		fail_exit2(ERR_SEM_CLOSE, philo);
	philo->death_status = 1;
	if (sem_close(philo->meal))
		fail_exit2(ERR_SEM_CLOSE, philo);
	philo->meal_status = 1;
	if (sem_unlink("FORK"))
		fail_exit2(ERR_SEM_UNLINK, philo);
	philo->fork_status= 0;
	if (sem_unlink("PRINT"))
		fail_exit2(ERR_SEM_UNLINK, philo);
	philo->print_status = 0;
	if (sem_unlink("DEATH"))
		fail_exit2(ERR_SEM_UNLINK, philo);
	philo->death_status = 0;
	if (sem_unlink("MEAL"))
		fail_exit2(ERR_SEM_UNLINK, philo);
	free(philo->tab_philo);
	exit(EXIT_SUCCESS);
}
