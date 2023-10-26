/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:22:06 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 19:27:53 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	end_cond(t_data *dt)
{
	int	i;

	i = -1;
	sem_wait(dt->lock);
	if (dt->glob_dead == TRUE)
	{
		sem_post(dt->lock);
		return (0);
	}
	while (++i < dt->nb_philos)
	{
		if (dt->philos[i].count_eat < dt->nb_meal || dt->nb_meal == -1)
		{
			sem_post(dt->lock);
			return (1);
		}
	}
	sem_post(dt->lock);
	return (0);
}

int	monitor_fct(void *data_ptr)
{
	t_data	*dt;
	int		i;

	dt = (t_data *)data_ptr;
	while (1)
	{
		i = -1;
		while (++i < dt->nb_philos)
		{
			///sem_wait(dt->lock);
			//sem_post(dt->lock);
			if (!end_cond(dt))
				return (1);
		}
	}
	return (0);
}
