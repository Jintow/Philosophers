/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:20:19 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/04 13:44:59 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Function that joins every argument in one only string which will be
	then splitted. This is to avoid parsing problem when user mixes different way
	of input : ex : ./a.out "arg1 arg2" arg3 
*/

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
