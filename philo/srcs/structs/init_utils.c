/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:12:48 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 13:58:24 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	verif_args(t_data *d)
{
	if (d->death_time < 0 || d->eat_time < 0 || d->pillow_time < 0
		|| d->nb_philos <= 0)
		ft_error(d, 0, NULL);
}

int	ft_mutex_init(t_data *datas)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(datas->lock), NULL))
		return (1);
	while (++i < datas->nb_philos)
	{
		if (pthread_mutex_init(&(datas->forks[i]), NULL))
		{
			pthread_mutex_destroy(&datas->lock);
			return (1);
		}
	}
	return (0);
}
