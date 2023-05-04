/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:58:12 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 10:01:52 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_inside(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i++] == c)
			return (1);
	}
	return (0);
}

int	ft_is_valid_format(char *str, char *comparing_base)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_inside(str[i], comparing_base))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
	{
		if (s2[i] == 0)
			return (0);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
