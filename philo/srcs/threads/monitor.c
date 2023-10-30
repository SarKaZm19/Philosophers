/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:20:43 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 13:44:11 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_cond(t_data *dt)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&dt->lock);
	if (dt->glob_dead == TRUE)
	{
		pthread_mutex_unlock(&dt->lock);
		return (0);
	}
	while (++i < dt->nb_philos)
	{
		if (dt->philos[i].count_eat < dt->nb_meal || dt->nb_meal == -1)
		{
			pthread_mutex_unlock(&dt->lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&dt->lock);
	return (0);
}

void	monitor_fct(void *data_ptr)
{
	t_data	*dt;
	int		i;

	dt = (t_data *)data_ptr;
	while (1)
	{
		i = -1;
		while (++i < dt->nb_philos)
		{
			pthread_mutex_lock(&dt->lock);
			if (gettime() - dt->philos[i].last_meal >= dt->death_time
				&& dt->philos[i].is_eating == FALSE)
			{
				dt->glob_dead = TRUE;
				printf("%llu	%d died\n", gettime() - dt->prog_start, i + 1);
			}
			pthread_mutex_unlock(&dt->lock);
			if (!end_cond(dt))
				return ;
		}
	}
	return ;
}
