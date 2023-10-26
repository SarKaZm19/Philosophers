/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:10:11 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 13:42:43 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(t_philo *ph, char *str)
{
	if (!end_cond(ph->datas))
		return ;
	pthread_mutex_lock(&ph->datas->lock);
	printf("%llu	%d %s\n", gettime() - ph->datas->prog_start, ph->id, str);
	pthread_mutex_unlock(&ph->datas->lock);
}
