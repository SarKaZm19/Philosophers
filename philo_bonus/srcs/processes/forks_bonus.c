/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:41:30 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 16:04:53 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	drop_forks(t_philo *philo)
{
	sem_post(philo->datas->forks);
	sem_post(philo->datas->forks);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->datas->forks);
	messages(philo, "has taken a fork");
	sem_wait(philo->datas->forks);
	messages(philo, "has taken a fork");
}
