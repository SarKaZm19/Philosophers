/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:10:11 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/24 18:39:55 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(t_philo *ph, char *str)
{
	//__uint64_t	time;

	if (check_state(ph->datas))
		return ;
	pthread_mutex_lock(&ph->datas->lock);
	//time = gettime() - dt->time_start;
	printf("%llu	%d %s\n", gettime() - ph->datas->prog_start, ph->id, str);
	pthread_mutex_unlock(&ph->datas->lock);
}
