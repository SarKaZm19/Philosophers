/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:22:06 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 21:14:41 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_data *datas, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		kill(datas->philos[i].pid, SIGKILL);
		i++;
	}
	free(datas->philos);
}

void	*monitor_fct(void *ph_arg)
{
	int		i;
	t_philo *ph;

	ph = ph_arg;
	while (1)
	{
		if (gettime() - ph->last_meal >= ph->datas->time_to_die)
		{
			sem_wait(ph->datas->lock);
			printf("%d	%d died\n", gettime() - ph->datas->prog_start, ph->id);
			i = -1;
			while (++i < ph->datas->nb_philos)
				sem_post(ph->datas->fed);
			return (NULL);
		}
	}
	return (NULL);
}
