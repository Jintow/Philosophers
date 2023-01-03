/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:42 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 17:48:51 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	char	**tab_info;
	t_philo	philo;
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (argc == 1)
		fail_exit(TOO_FEW_ARG, NULL);
	tab_info = init_args(&argv[1]);
	central_checking(tab_info);
	init_struct_philo(&philo, tab_info);
	activate_simulation(&philo);
	// *philo.tab_philo[2].lock2 = 2;
	// printf("%d, time_death : %d, time_eat : %d, time_sleep : %d\n",(philo.tab_philo[0].time0_sim.tv_usec - current.tv_usec), \
	// 	philo.tab_philo[2].time_death, philo.tab_philo[2].time_eat, philo.tab_philo[2].time_sleep);
	// printf("lock1 :%d, lock2 : %d\n", *(philo.tab_philo[2].lock1), *(philo.tab_philo[2].lock2));
	// printf("lock1 :%p, lock2 : %p\n", (philo.tab_philo[2].lock1), (philo.tab_philo[2].lock2));

}
