/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:43:23 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/24 21:22:04 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_args(t_data *d)
{
	if (d->death_time < 0 || d->eat_time < 0 || d->pillow_time < 0
		|| d->nb_philos <= 0)
	{
		ft_error(d, 0, NULL);
		return (1);
	}
	return (0);
}

void	init_philos(t_data *datas)
{	
	int	i;

	i = -1;
	while (++i < datas->nb_philos)
	{
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

int	ft_alloc(t_data *datas)
{
	int	i;

	i = -1;
	datas->philos = malloc(sizeof(t_philo) * datas->nb_philos);
	if (!datas->philos)
		return (ft_error(datas, 1, "malloc"), 1);
	memset(datas->philos, 0, datas->nb_philos);
	datas->forks = malloc(sizeof(pthread_mutex_t) * datas->nb_philos);
	if (!datas->forks)
		return (ft_error(datas, 1, "malloc"), 1);
	memset(datas->forks, 0, datas->nb_philos);
	datas->thid = malloc(sizeof(t_philo) * datas->nb_philos);
	if (!datas->thid)
		return (ft_error(datas, 1, "malloc"), 1);
	memset(datas->thid, 0, datas->nb_philos);
	if (pthread_mutex_init(&(datas->lock), NULL))
		return (ft_error(datas, 1, "mutex_init"), 1);
	while (++i < datas->nb_philos)
		if (pthread_mutex_init(&(datas->forks[i]), NULL))
			return (ft_error(datas, 1, "mutex_init"), 1);
	return (0);
}

int	init_datas(t_data *datas, int ac, char **av)
{
	datas->nb_philos = ft_atoi(av[1]);
	if (ac == 6)
		datas->nb_meal = ft_atoi(av[5]);
	datas->death_time = (__uint64_t) ft_atoi(av[2]);
	datas->eat_time = (__uint64_t) ft_atoi(av[3]);
	datas->pillow_time = (__uint64_t) ft_atoi(av[4]);
	datas->err_catch = verif_args(datas);
	datas->err_catch = ft_alloc(datas);
	if (datas->err_catch)
		return (1);
	datas->prog_start = gettime();
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
