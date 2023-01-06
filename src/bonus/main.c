/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:42 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 13:48:56 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc <= 4)
		fail_exit(TOO_FEW_ARG, NULL);
	if (argc >= 7)
		fail_exit(TOO_MANY_ARGS, NULL);
	central_checking(&argv[1]);
	init_struct_philo(&philo, &argv[1]);
	activate_simulation(&philo);
}
