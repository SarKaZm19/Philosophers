/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:08:46 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/18 19:22:06 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_forks(t_philo *ph)
{
	pthread_mutex_unlock(ph->l_fork);
	//messages(philo, "dropped left fork");
	pthread_mutex_unlock(ph->r_fork);
	//messages(philo, "dropped right fork");
}

void	take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->r_fork);
	messages(ph, "has taken a fork");
	pthread_mutex_lock(ph->l_fork);
	messages(ph, "has taken a fork");
}
