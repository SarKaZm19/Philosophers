/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:52:34 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 00:47:49 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	verif_args(t_data *d)
{
	if (d->time_to_die < 0 || d->time_to_eat < 0 || d->time_to_sleep < 0
		|| d->nb_philos <= 0)
		ft_error(d, 0, NULL);
}

int	ft_sem_init(t_data *datas)
{
/* 	int	i;

	i = -1; */
	sem_unlink("s_forks");
	sem_unlink("s_lock");
	sem_unlink("s_process");
	datas->forks = sem_open("s_forks", O_CREAT, 0600, datas->nb_philos);
	if (!datas->forks)
		return (1);
	datas->lock = sem_open("s_lock", O_CREAT, 0600, 1);
	if (!datas->lock)
	{
		sem_close(datas->forks);
		sem_unlink("s_forks");
		return (1);
	}
	return (0);
}

/* int ft_sem_init(t_data *datas)
{
    int i;

    i = -1;

    while (++i < datas->nb_philos)
    {
        datas->forks[i] = sem_open("s_forks", O_CREAT, 0664, 1);
        if (datas->forks[i] == SEM_FAILED)
        {
            perror("sem_open");
            return (1);
        }
    }
    datas->lock = sem_open("s_lock", O_CREAT, 0664, 1);
    if (datas->lock == SEM_FAILED)
    {
        perror("sem_open");
        return (1);
    }

    return (0);
} */
