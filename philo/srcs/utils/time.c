/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:16:47 by fvastena          #+#    #+#             */
/*   Updated: 2023/09/30 23:58:11 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(__useconds_t time)
{
	__uint64_t	start;

	start = gettime();
	while ((gettime() - start) < time)
		usleep(time / 10);
	return (0);
}

__uint64_t gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / 1000));
}