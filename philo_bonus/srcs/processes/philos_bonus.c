/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:39:36 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 21:16:08 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	if ((philo->id & 1) == 0)
		ft_usleep(philo->datas->time_to_eat / 2);
	while (1)
	{
		sem_wait(philo->datas->forks);
		messages(philo, "has taken a fork");
		if (philo->datas->nb_philos == 1)
			return ;
		sem_wait(philo->datas->forks);
		messages(philo, "has taken a fork");
		messages(philo, "is eating");
		philo->last_meal = gettime();
		ft_usleep(philo->datas->time_to_eat);
		drop_forks(philo);
		++philo->count_eat;
		if (philo->count_eat == philo->datas->nb_meal)
			sem_post(philo->datas->fed);
		messages(philo, "is sleeping");
		ft_usleep(philo->datas->time_to_sleep);
		messages(philo, "is thinking");
	}
	return ;
}

void	exec_philo(t_philo *philos)
{
	int	i;

	if (pthread_create(&philos->thid, NULL, &monitor_fct, philos) != 0)
	{
		i = -1;
		while (++i < philos->datas->nb_philos)
			sem_post(philos->datas->fed);
		exit(EXIT_FAILURE);
	}
	routine(philos);
	pthread_join(philos->thid, NULL);
	exit(EXIT_SUCCESS);
}

void	init_philos(t_data *datas, t_philo *philo, int index)
{
	philo->id = index;
	philo->last_meal = datas->prog_start;
	philo->count_eat = 0;
	philo->datas = datas;
}

int	processing(t_data *datas)
{
	int	i;

	i = 0;
	datas->prog_start = gettime();
	while (i < datas->nb_philos)
	{
		init_philos(datas, &datas->philos[i], i + 1);
		datas->philos[i].pid = fork();
		if (datas->philos[i].pid == -1)
		{
			kill_processes(datas, i);
			free(datas->philos);
			ft_destroy_semaphores(datas);
			return(1);
		}
		else if (!datas->philos[i].pid)
			exec_philo(&datas->philos[i]);
		i++;
	}
	return (0);
}
