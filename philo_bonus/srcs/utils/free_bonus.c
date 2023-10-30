/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:52:09 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 01:10:23 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_destroy_semaphores(t_data *datas)
{
	sem_close(datas->forks);
	sem_close(datas->lock);
	sem_close(datas->process);
	sem_unlink("s_forks");
	sem_unlink("s_lock");
	sem_unlink("s_process");
}

void	ft_free_datas(t_data **datas)
{
	/* if ((*datas)->philos)
		free((*datas)->philos); */
	if ((*datas)->pid)
		free((*datas)->pid);
}
