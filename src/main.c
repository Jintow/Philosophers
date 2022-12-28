/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:42 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/28 16:29:06 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	char	**tab_info;
	t_philo	philo;

	if (argc == 1)
		fail_exit(TOO_FEW_ARG, NULL);
	tab_info = init_args(&argv[1]);
	central_checking(tab_info);
	init_struct_philo(&philo, tab_info);
	// ft_printf("NB PHILO : %d\n", philo.tab_philo[654].time_sleep);

}
