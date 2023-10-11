/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:16:47 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/11 12:10:52 by fvastena         ###   ########.fr       */
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


void	time_test(void)
{
	struct timeval	start_time;
	struct timeval	end_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&start_time, NULL);

	printf("%ld\n", start_time.tv_sec);
	printf("%d\n", start_time.tv_usec);
	int ret;
	char buf;
	while (1)
	{
		ret = read(0, &buf, 1);
		if (ret == -1)
			break ;
		if (buf == 'C')
			break;
	}
	gettimeofday(&end_time, NULL);
	gettimeofday(&end_time, NULL);
	if (end_time.tv_usec < start_time.tv_usec) {
        end_time.tv_sec--;
        end_time.tv_usec += 1000000; // 1 million (microseconds) to correct for overflow
    }
	printf("%ld\n", end_time.tv_sec - start_time.tv_sec);
	printf("%d\n", end_time.tv_usec - start_time.tv_usec);
	time_t newtime_s;
	suseconds_t newtime_us;
	newtime_s = end_time.tv_sec - start_time.tv_sec; 
	newtime_us = end_time.tv_usec - start_time.tv_usec;
	printf("time elapsed = %ld,%d\n", newtime_s, newtime_us);
}