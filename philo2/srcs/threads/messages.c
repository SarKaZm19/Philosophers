/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:10:11 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/18 16:20:36 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(t_philo *ph, char *str)
{
	//__uint64_t	time;

	pthread_mutex_lock(&ph->datas->write);
	//time = gettime() - dt->time_start;
	printf("%llu %d %s\n", gettime() - ph->datas->prog_start, ph->id, str);
	pthread_mutex_unlock(&ph->datas->write);
}
