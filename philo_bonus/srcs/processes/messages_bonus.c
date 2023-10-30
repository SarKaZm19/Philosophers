/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:50:18 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 20:25:46 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	messages(t_philo *philo, char *str)
{
	sem_wait(philo->datas->lock);
	printf("%d	%d %s\n", gettime() - philo->datas->prog_start, philo->id, str);
	sem_post(philo->datas->lock);
}
