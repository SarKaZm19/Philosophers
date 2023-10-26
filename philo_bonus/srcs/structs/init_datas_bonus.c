/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:52:41 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 19:41:56 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_alloc(t_data *datas)
{
	datas->philos = malloc(sizeof(t_philo) * datas->nb_philos);
	if (!datas->philos)
		return (ft_error(datas, 1, "malloc"));
	memset(datas->philos, 0, datas->nb_philos);
	if (ft_sem_init(datas))
		return (ft_error(datas, 1, "sem_open"));
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
		datas->philos[i].time_to_die = datas->death_time;
		datas->philos[i].time_to_eat = datas->eat_time;
		datas->philos[i].time_to_sleep = datas->pillow_time;
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
}
