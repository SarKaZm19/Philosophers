/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:41:30 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/29 21:41:39 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	drop_forks(t_data *datas)
{
	sem_post(datas->forks);
	sem_post(datas->forks);
}

void	take_forks(t_data *datas)
{
	sem_wait(datas->forks);
	messages(datas, "has taken a fork");
	sem_wait(datas->forks);
	messages(datas, "has taken a fork");
}