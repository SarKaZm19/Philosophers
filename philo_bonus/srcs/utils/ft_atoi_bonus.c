/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:57:44 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/19 13:57:48 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'
		|| c == ' ')
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
	while (ft_isspace(tmp[i]))
		i++;
	if (tmp[i] == '+' || tmp[i] == '-')
	{
		if (tmp[i] == '-')
			return(-1);
		i++;
	}
	while (ft_isdigit(tmp[i]))
	{
		nb = nb * 10 + tmp[i] - 48;
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return (sign * nb);
}