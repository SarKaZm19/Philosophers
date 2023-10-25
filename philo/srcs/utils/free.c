/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:43:42 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/25 17:51:16 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutexes(t_data **datas)
{
	int	i;

	i = -1;
	while (++i < (*datas)->nb_philos)
		pthread_mutex_destroy(&(*datas)->forks[i]);
	pthread_mutex_destroy(&(*datas)->lock);
}

void	ft_free_datas(t_data **datas)
{
	if ((*datas)->thid)
		free((*datas)->thid);
	if ((*datas)->philos)
		free((*datas)->philos);
	if ((*datas)->forks)
		free((*datas)->forks);
}
