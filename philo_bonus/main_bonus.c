/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:09:48 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 20:30:15 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exec_philo(t_philo *ph)
{
	if ((ph->id & 1) == 0)
	{
		messages(ph, "is thinking");
		ft_usleep(ph->time_to_eat / 2);
	}
	while (ph->datas->glob_dead == FALSE)
	{
		//sem_wait(ph->datas->process);
		take_forks(ph);
		messages(ph, "is eating");
		sem_wait(ph->datas->lock);
		ph->last_meal = gettime();
		if (ph->datas->nb_meal > 0)
			ph->count_eat++;
		if (ph->datas->nb_meal == ph->count_eat)
		{
			//free;
			exit(0);
		}
		sem_post(ph->datas->lock);
		ft_usleep(ph->time_to_eat);
		drop_forks(ph);
		messages(ph, "is sleeping");
		ft_usleep(ph->time_to_sleep);
		messages(ph, "is thinking");
		//sem_post(ph->datas->process);
	}
}

void	processing(t_data *datas)
{
	int	i;
	int	status;

	i = 0;
	while (i < datas->nb_philos)
	{
		datas->philos[i].pid = fork();
		if (datas->philos[i].pid == -1)
		{
			printf("failed ?\n");
			exit(1); // a protect
		}
		else if (!datas->philos[i].pid)
		{
			datas->philos[i].last_meal = gettime();
			exec_philo(&datas->philos[i]);
			// free_datas
		}
		i++;
	}
	i = -1;
	while (++i < datas->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < datas->nb_philos)
				kill(datas->philos[i].pid, SIGKILL);
		}
	}
	ft_destroy_semaphores(datas);
	ft_free_datas(&datas);
}

int	main(int ac, char **av)
{
	t_data	datas;

	if (ac < 5 || ac > 6)
		return (usage_error());
	//printf("init_null...\n");
	init_null(&datas);
	//printf("init_datas...\n");
	init_datas(&datas, ac, av);
	//printf("threading...\n");
	processing(&datas);
	//printf("end...\n");

}