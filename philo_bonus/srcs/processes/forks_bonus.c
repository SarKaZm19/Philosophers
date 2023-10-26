/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:41:30 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 17:52:28 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	drop_forks(t_philo *ph)
{
	sem_post(ph->datas->forks);
	sem_post(ph->datas->forks);

}

void	take_forks(t_philo *ph)
{
	sem_wait(ph->datas->forks);
	messages(ph, "has taken a fork");
	sem_wait(ph->datas->forks);
	messages(ph, "has taken a fork");
}