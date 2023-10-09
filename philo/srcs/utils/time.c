/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:16:47 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/09 13:50:48 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	ft_usleep(uint64_t time)
// {
// 	uint64_t	start;

// 	start = gettime();
// 	while ((gettime() - start) < (uint64_t)time)
// 		usleep(time / 10);
// }

void	ft_usleep(uint64_t ms)
{
	const uint64_t	start = gettime();

	while (gettime() - start < ms)
		usleep(100);
}

__uint64_t gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}