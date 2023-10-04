/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:43:23 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/03 19:11:54 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_data *datas)
{
	int	i;

	i = -1;
	while (++i < datas->nb_philos)
		pthread_mutex_init(&(datas->forks[i]), NULL);
	//pthread_mutex_init(&(datas->forks[i]), NULL);
}

void	init_datas(t_data *datas, int ac, char **av)
{
	//need to catch errors + ft_atoi exclusions and var verif cuz uint_64 = UNSIGNED long so -1 pas working
	printf("init_datas_var...\n");
	datas->nb_philos = ft_atoi(av[1]);
	datas->time_to_die = (__uint64_t) ft_atoi(av[2]);
	datas->time_to_eat = (__uint64_t) ft_atoi(av[3]);
	datas->time_to_sleep = (__uint64_t) ft_atoi(av[4]);
	/* if (datas->time_to_die < 0 || datas->time_to_eat < 0 ||datas->time_to_sleep < 0 || datas->time_to_think < 0)
		datas->nb_philos = -1; */
	if (ac == 6)
	{
		datas->nb_meal = ft_atoi(av[5]);
		if (datas->nb_meal == 0)
			return ;
	}
	printf("init_alloc_var...\n");
	datas->eating = malloc(sizeof(int) * datas->nb_philos);
	if (!datas->eating)
		return ;
	memset(datas->eating, FALSE, datas->nb_philos);

	datas->count_eat = malloc(sizeof(int) * datas->nb_philos);
	if (!datas->count_eat)
		return ;
	memset(datas->count_eat, 0, datas->nb_philos);

	datas->last_meal = malloc(sizeof(__uint64_t) * datas->nb_philos);
	if (!datas->last_meal)
		return ;
	memset(datas->last_meal, 0, datas->nb_philos);

	datas->philos = malloc(sizeof(pthread_t) * datas->nb_philos);
	if (!datas->philos)
		return ;
	memset(datas->philos, 0, datas->nb_philos);

	datas->forks = malloc(sizeof(pthread_mutex_t) * datas->nb_philos);
	if (!datas->forks)
		return ;
	memset(datas->forks, 0, datas->nb_philos);

	printf("init_forks lock...\n");
	init_forks(datas);
	printf("init_datas lock...\n");
	pthread_mutex_init(&datas->lock, NULL);
	printf("init_write lock...\n");
	pthread_mutex_init(&datas->write, NULL);
	printf("print_datas...\n");
	print_datas(datas);
}

void	init_null(t_data *datas)
{
	datas->dead = FALSE;
	datas->nb_philos = 0;
	datas->id = 0;
	datas->nb_meal = 0;
	datas->eating = NULL;
	datas->count_eat = NULL;
	datas->time_to_die = 0;
	datas->time_to_eat = 0;
	datas->time_to_sleep = 0;
	datas->time_start = 0;
	datas->philos = NULL;
	datas->forks = NULL;
}
