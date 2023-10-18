/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:43:23 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/18 19:31:55 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void	init_ids(t_data *datas)
{
	int	i;

	i = -1;
	while (++i < datas->nb_philos)
	{
		datas->id[i] = i;
		printf("id[%d] = %d", i, datas->id[i]);
	}
} */
void	init_forks(t_data *datas)
{
	int	i;

	i = -1;
	while (++i < datas->nb_philos)
		pthread_mutex_init(&(datas->forks[i]), NULL);
	//pthread_mutex_init(&(datas->forks[i]), NULL);
}

void	init_philos(t_data *datas, char **av)
{	
	int	i;

	i = -1;
	while (++i < datas->nb_philos)
	{
		datas->philos[i].id = i + 1;
		datas->philos[i].is_dead = FALSE;
		datas->philos[i].is_eating = FALSE;
		datas->philos[i].count_eat = 0;
		datas->philos[i].time_to_die = datas->death_time;
		datas->philos[i].time_to_eat = (__uint64_t) ft_atoi(av[3]);
		datas->philos[i].time_to_sleep = (__uint64_t) ft_atoi(av[4]);
		datas->philos[i].last_meal = 0;
		datas->philos[i].r_fork = &datas->forks[i];
		if (i != datas->nb_philos - 1)
			datas->philos[i].l_fork = &datas->forks[i + 1];
		else
			datas->philos[i].l_fork = &datas->forks[0];
		pthread_mutex_init(&datas->philos[i].dead_m, NULL);
		datas->philos[i].datas = datas;
	}
}

void	init_datas(t_data *datas, int ac, char **av)
{
	//need to catch errors + ft_atoi exclusions and var verif cuz uint_64 = UNSIGNED long so -1 pas working
	printf("init_datas_var...\n");

	/* if (datas->time_to_die < 0 || datas->time_to_eat < 0 ||datas->time_to_sleep < 0 || datas->time_to_think < 0)
		datas->nb_philos = -1; */
	datas->glob_dead = FALSE;
	datas->nb_philos = ft_atoi(av[1]);
	if (ac == 6)
	{
		datas->nb_meal = ft_atoi(av[5]);
		if (datas->nb_meal == 0)
			return ;
	}
	datas->death_time = (__uint64_t) ft_atoi(av[2]);
	printf("init_alloc_var...\n");
	datas->philos = malloc(sizeof(t_philo) * datas->nb_philos);
	if (!datas->philos)
		return ;

	datas->thid = malloc(sizeof(t_philo) * datas->nb_philos);
	if (!datas->thid)
		return ;

	datas->forks = malloc(sizeof(pthread_mutex_t) * datas->nb_philos);
	if (!datas->forks)
		return ;
	memset(datas->forks, 0, datas->nb_philos);

	//printf("init_forks lock...\n");
	init_forks(datas);
	//init_ids(datas);
	printf("init_philos...\n");
	init_philos(datas, av);
	//printf("init_datas lock...\n");
	pthread_mutex_init(&datas->lock, NULL);
	pthread_mutex_init(&datas->glob_dead_m, NULL);
	//pthread_mutex_init(&datas->dead_mt, NULL);
	//printf("init_write lock...\n");
	pthread_mutex_init(&datas->write, NULL);
	//printf("print_datas...\n");

	print_datas(datas);
}

void	init_null(t_data *datas)
{
	datas->glob_dead = FALSE;
	datas->nb_philos = 0;
	datas->nb_meal = -1;
	datas->prog_start = 0;
	datas->philos = NULL;
	datas->forks = NULL;
}
