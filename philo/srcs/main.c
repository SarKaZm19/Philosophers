/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:09 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/25 18:51:27 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eating(t_philo *ph)
{
	take_forks(ph);
	messages(ph, "is eating");
	pthread_mutex_lock(&ph->datas->lock);
	ph->is_eating = TRUE;
	ph->last_meal = gettime();
	if (ph->datas->nb_meal >= 0)
		ph->count_eat++;
	pthread_mutex_unlock(&ph->datas->lock);
	ft_usleep(ph->time_to_eat);
	ph->is_eating = FALSE;
	drop_forks(ph);
}

void	*thread_function(void *ph_ptr)
{
	t_philo		*ph;

	ph = (t_philo *)ph_ptr;
	if ((ph->id & 1) == 0)
		ft_usleep(ph->time_to_eat / 2);
	if (ph->datas->nb_philos == 1)
	{
		take_forks(ph);
		ft_usleep(ph->time_to_die);
		drop_forks(ph);
	}
	while (!check_state(ph->datas))
	{
		p_eating(ph);
		messages(ph, "is sleeping");
		ft_usleep(ph->time_to_sleep);
		messages(ph, "is thinking");
	}
	return (NULL);
}

void	print_datas(t_data *datas)
{
	printf("err_catch = %d\n", datas->err_catch);
	printf("glob_dead = %d\n", datas->glob_dead);
	printf("nb_meal = %d\n", datas->nb_meal);
	printf("nb_philos = %d\n", datas->nb_philos);
	printf("prog_start = %llu\n", datas->prog_start);
	printf("time_to_die = %llu\n", datas->death_time);
	printf("time_to_eat = %llu\n", datas->eat_time);
	printf("time_to_sleep = %llu\n", datas->pillow_time);
	printf("lock = %p\n", &datas->lock);
	int i = 0;
	while (i < datas->nb_philos)
	{
		printf("fork[%d] = %p\n", i, &datas->forks[i]);
		i++;
	}
	i = 0;
	while (i < datas->nb_philos)
	{
		printf("philo->id = %d\n", datas->philos[i].id);
		printf("thid = %p\n", datas->thid[i]);
		printf("philo->count_eat = %d\n", datas->philos[i].count_eat);
		printf("philo->last_meal = %llu\n", datas->philos[i].last_meal);
		printf("philo->time_to_die = %llu\n", datas->philos[i].time_to_die);
		printf("philo->time_to_eat = %llu\n", datas->philos[i].time_to_eat);
		printf("philo->time_to_sleep = %llu\n", datas->philos[i].time_to_sleep);
		printf("philo->r_fork = %p\n", datas->philos[i].r_fork);
		printf("philo->l_fork = %p\n", datas->philos[i].l_fork);
		i++;
	}
}

void	threading(t_data *datas)
{
	int	i;

	i = 0;
	while (i < datas->nb_philos)
	{
		if (pthread_create(&(datas->thid[i]), NULL, &thread_function,
				(void *)&datas->philos[i]) != 0)
			return (ft_error(datas, 1, "pthread_create"));
		i++;
	}
	monitor_fct(datas);
	i = 0;
	while (i < datas->nb_philos)
	{
		if (pthread_join(datas->thid[i], NULL) != 0)
			return (ft_error(datas, 1, "pthread_join"));
		i++;
	}
	ft_destroy_mutexes(&datas);
	ft_free_datas(&datas);
}

int	main(int ac, char **av)
{
	t_data			datas;

	if (ac < 5 || ac > 6)
		return (usage_error());
	else
	{
		init_null(&datas);
		if (init_datas(&datas, ac, av))
			return (1);
		threading(&datas);
	}
	return (0);
}
