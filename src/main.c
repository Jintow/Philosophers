/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:42 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 11:25:00 by Teiki            ###   ########.fr       */
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
	ft_printf("%d, NB PHILO : %d\n",(philo.tab_philo[0].time0_sim.tv_usec - current.tv_usec), philo.tab_philo[654].time_sleep);

}
