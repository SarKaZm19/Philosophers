/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:50:18 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 00:36:15 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	messages(t_data *datas, char *str)
{
/* 	if (!end_cond(ph->datas))
		return ; */
	sem_wait(datas->lock);
	printf("%ld	%d %s\n", gettime() - datas->prog_start, datas->philos.id, str);
	sem_post(datas->lock);
}