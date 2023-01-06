/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:05:18 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/06 10:07:55 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nb, size_t size)
{
	void	*p;

	if (nb != 0 && 2147483647 / nb < size)
		return (NULL);
	p = malloc(nb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nb * size);
	return (p);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned int	nb;
	int				sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] && ((str[i] == '-') || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = str[i] - 48 + (nb * 10);
		i++;
	}
	return (sign * (int)nb);
}
