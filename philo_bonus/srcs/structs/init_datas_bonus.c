/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:52:41 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 21:17:00 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_destroy_semaphores(t_data *datas)
{
	sem_close(datas->forks);
	sem_close(datas->lock);
	sem_close(datas->fed);
	sem_unlink("/s_forks");
	sem_unlink("/s_lock");
	sem_unlink("/fed");
}

static int	ft_sem_init(t_data *datas)
{
	sem_unlink("/s_forks");
	sem_unlink("/s_lock");
	sem_unlink("/s_fed");
	datas->forks = sem_open("/s_forks", O_CREAT, 0644, datas->nb_philos);
	if (!datas->forks)
		return (1);
	datas->lock = sem_open("/s_lock", O_CREAT, 0644, 1);
	if (!datas->lock)
	{
		sem_close(datas->forks);
		sem_unlink("/s_forks");
		return (1);
	}
	datas->fed = sem_open("/s_fed", O_CREAT, 0644, 0);
	if (!datas->fed)
	{
		sem_close(datas->forks);
		sem_close(datas->lock);
		sem_unlink("/s_unlink");
		sem_unlink("/s_forks");
		return (1);
	}
	return (0);
}

static void	ft_alloc(t_data *datas)
{
	if (ft_sem_init(datas))
		return (ft_error(datas, 1, "sem_open"));
	datas->philos = malloc(sizeof(*datas->philos) * datas->nb_philos);
	if (!datas->philos)
		return (ft_error(datas, 1, "malloc"));
}

static void	init_times(t_data *datas, int ac, char **av)
{
	long long	dtime;
	long long	etime;
	long long	stime;

	datas->nb_philos = ft_atoi(av[1]);
	if (ac == 6)
	{
		datas->nb_meal = ft_atoi(av[5]);
		if (datas->nb_meal <= 0)
			return (ft_error(datas, 0, NULL));
	}
	dtime = ft_atoi(av[2]);
	etime = ft_atoi(av[3]);
	stime = ft_atoi(av[4]);
	if (dtime <= 0 || etime <= 0 || stime <= 0 || datas->nb_philos <= 0)
		return (ft_error(datas, 0, NULL));
	datas->time_to_die = (int) dtime;
	datas->time_to_eat = (int) etime;
	datas->time_to_sleep = (int) stime;
}

int	init_datas(t_data *datas, int ac, char **av)
{
	datas->err_catch = 0;
	init_times(datas, ac, av);
	if (datas->err_catch)
		return (1);
	ft_alloc(datas);
	if (datas->err_catch)
		return (1);
	return (0);
}
