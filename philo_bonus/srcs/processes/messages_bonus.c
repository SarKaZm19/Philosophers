/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:50:18 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 17:55:34 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	messages(t_philo *ph, char *str)
{
	if (!end_cond(ph->datas))
		return ;
	sem_wait(ph->datas->lock);
	printf("%llu	%d %s\n", gettime() - ph->datas->prog_start, ph->id, str);
	sem_post(ph->datas->lock);
}