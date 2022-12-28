/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:20:19 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/27 13:56:38 by Teiki            ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	i = -1;
	while (argv[++i])
	{
		value = ft_strjoin_free_s1(value, argv[i]);
		if (!value)
			exit(EXIT_FAILURE);
		value = ft_strjoin_free_s1(value, " ");
		if (!value)
			exit(EXIT_FAILURE);
	}
	tab_nb = ft_split(value, ' ');
	free(value);
	if (!tab_nb)
		exit(EXIT_FAILURE);
	return (tab_nb);
}
