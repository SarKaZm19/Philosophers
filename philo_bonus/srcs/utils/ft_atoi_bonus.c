/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:52:17 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 14:52:20 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long			nb;
	size_t			i;
	int				sign;
	unsigned char	*tmp;

	sign = 1;
	nb = 0;
	i = 0;
	tmp = (unsigned char *)nptr;
	if (!ft_isdigit(tmp[i]))
		return (-1);
	while (ft_isdigit(tmp[i]))
	{
		nb = nb * 10 + tmp[i] - 48;
		if (nb > INT_MAX)
			return (-1);
		i++;
	}
	if (tmp[i])
		return (-1);
	return (sign * nb);
}
