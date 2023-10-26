/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:09 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 14:16:10 by fvastena         ###   ########.fr       */
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
	if (ph->datas->nb_meal > 0)
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
	while (end_cond(ph->datas))
	{
		p_eating(ph);
		messages(ph, "is sleeping");
		ft_usleep(ph->time_to_sleep);
		messages(ph, "is thinking");
	}
	return (NULL);
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
