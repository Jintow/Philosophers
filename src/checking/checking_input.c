/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:22:19 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 12:09:28 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	characters_checking(char **tab);
int	overflowing_checking(char **tab);

/*
	Central checking function.
	- Return (0) if there is non-digit char in the arguments
		or an overflowed number.
	- Return (1) if everything is good.
*/

int	central_checking(char **tab_arg)
{
	if (!characters_checking(tab_arg))
		fail_exit(NO_VALID_ARGS, tab_arg);
	if (!overflowing_checking(tab_arg))
		fail_exit(NO_VALID_ARGS, tab_arg);
	return (1);
}

/*
	Function that check if there is only digits in input arguments.
*/

int	characters_checking(char **tab)
{
	int		i;
	char	*nb;

	i = 0;
	while (tab[i])
	{
		nb = tab[i];	
		if (!(*nb))
			return (0);
		if (!ft_is_valid_format(nb, BASE_DEC))
			return (0);
		i++;
	}
	return (1);
}

int	overflowed_nb(char *nb)
{
	if (ft_strcmp(CHAR_INT_MAX, nb) < 0)
		return (1);
	return (0);
}

/*
	Function that checks the potential overflowing input arguments.
	First zeros are passed, len of the number is compared to the maximum 
	integer len (10). 
*/

int	overflowing_checking(char **tab)
{
	int		i;
	int		len;
	char	*nb;

	i = 0;
	while (tab[i])
	{
		nb = tab[i];
		while (*nb == '0')
			nb++;
		len = ft_strlen(nb);
		if (len > 10)
			return (0);
		else if (len == 10 && overflowed_nb(nb))
			return (0);
		i++;
	}
	return (1);
}
