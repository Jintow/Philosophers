/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:20:19 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/03 23:30:59 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	**init_args(char **argv)
{
	char	*value;
	char	**tab_nb;
	int		i;

	value = ft_calloc(1, sizeof(char));
	if (!value)
		fail_exit(ERR_MALLOC, NULL);
	i = -1;
	while (argv[++i])
	{
		value = ft_strjoin_free_s1(value, argv[i]);
		if (!value)
			fail_exit(ERR_MALLOC, NULL);
		value = ft_strjoin_free_s1(value, " ");
		if (!value)
			fail_exit(ERR_MALLOC, NULL);
	}
	tab_nb = ft_split(value, ' ');
	free(value);
	if (!tab_nb)
		fail_exit(ERR_MALLOC, NULL);
	return (tab_nb);
}
