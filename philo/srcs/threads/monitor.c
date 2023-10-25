/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:20:43 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/25 18:53:22 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_data *dt)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&dt->lock);
	if (dt->glob_dead == TRUE)
	{
		pthread_mutex_unlock(&dt->lock);
		return (1);
	}
	while (++i < dt->nb_philos)
	{
		if (dt->philos[i].count_eat < dt->nb_meal || dt->nb_meal == -1)
		{
			pthread_mutex_unlock(&dt->lock);
			return (0);
		}
	}
	pthread_mutex_unlock(&dt->lock);
	return (1);
}

void	*monitor_fct(void *data_ptr)
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
			if (check_state(dt))
				return (NULL);
		}
	}
	return (NULL);
}
