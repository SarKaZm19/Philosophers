/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:57:41 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/19 14:33:42 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_datas(t_data *datas, int ac, char **av)
{
	datas->nb_philos = ft_atoi(av[1]);
	datas->time_to_die = (u_int64_t) ft_atoi(av[2]);
	datas->time_to_eat = (u_int64_t) ft_atoi(av[3]);
	datas->time_to_sleep = (u_int64_t) ft_atoi(av[4]);
	if (ac == 6)
		datas->nb_meal = (u_int64_t) ft_atoi(av[5]);
	else
		datas->nb_meal = -1;
	printf("alloc...\n");
	datas->count_eat = malloc(sizeof(int) * datas->nb_philos);
	if (!datas->count_eat)
		exit(1);
	datas->pids = malloc(sizeof(pid_t) * datas->nb_philos);
	if (!datas->pids)
		exit(1);
	printf("init_sem..\n");
	datas->f_lock = sem_open("/sem_forks", O_CREAT, 0666, datas->nb_philos / 2);
	datas->w_lock = sem_open("/sem_write", O_CREAT, 0666, datas->nb_philos / 2);
	datas->e_lock = sem_open("/sem_eat", O_CREAT, 0666, datas->nb_philos / 2);

}

void	init_null(t_data *datas)
{
	datas->dead = FALSE;
	datas->count_eat = NULL;
}