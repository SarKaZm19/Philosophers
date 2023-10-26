/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:43:23 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 18:44:48 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_alloc(t_data *datas)
{
	datas->philos = malloc(sizeof(t_philo) * datas->nb_philos);
	if (!datas->philos)
		return (ft_error(datas, 1, "malloc"));
	memset(datas->philos, 0, datas->nb_philos);
	datas->forks = malloc(sizeof(pthread_mutex_t) * datas->nb_philos);
	if (!datas->forks)
		return (ft_error(datas, 1, "malloc"));
	memset(datas->forks, 0, datas->nb_philos);
	datas->thid = malloc(sizeof(t_philo) * datas->nb_philos);
	if (!datas->thid)
		return (ft_error(datas, 1, "malloc"));
	memset(datas->thid, 0, datas->nb_philos);
	if (ft_mutex_init(datas))
		return (ft_error(datas, 1, "mutex_init"));
}

static void	init_philos(t_data *datas)
{
	int	i;

	i = -1;
	while (++i < datas->nb_philos)
	{
		datas->philos[i].is_eating = FALSE;
		datas->philos[i].id = i + 1;
		datas->philos[i].count_eat = 0;
		datas->philos[i].last_meal = datas->prog_start;
		datas->philos[i].r_fork = &datas->forks[i];
		datas->philos[i].time_to_die = datas->death_time;
		datas->philos[i].time_to_eat = datas->eat_time;
		datas->philos[i].time_to_sleep = datas->pillow_time;
		if (i != datas->nb_philos - 1)
			datas->philos[i].l_fork = &datas->forks[i + 1];
		else
			datas->philos[i].l_fork = &datas->forks[0];
		datas->philos[i].datas = datas;
	}
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
	datas->death_time = (__uint64_t) dtime;
	datas->eat_time = (__uint64_t) etime;
	datas->pillow_time = (__uint64_t) stime;
}

int	init_datas(t_data *datas, int ac, char **av)
{
	init_times(datas, ac, av);
	if (datas->err_catch)
		return (1);
	verif_args(datas);
	ft_alloc(datas);
	if (datas->err_catch)
		return (1);
	datas->prog_start = gettime();
	if (datas->prog_start == -1)
		return (1);
	init_philos(datas);
	return (0);
}

void	init_null(t_data *datas)
{
	datas->glob_dead = FALSE;
	datas->err_catch = 0;
	datas->nb_meal = -1;
	datas->prog_start = 0;
	datas->philos = NULL;
	datas->thid = NULL;
	datas->forks = NULL;
}
