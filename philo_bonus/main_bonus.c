/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:09:48 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/19 14:37:21 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exec_philo(t_data *datas, int i)
{
	if (i == 1)
		datas->dead = 1;
	else
	{
		sleep(1);
		printf("dead = %d\n", datas->dead);
	}
}

void	processing(t_data *datas)
{
	int	i;

	i = 0;
	//printf("nb_philo = %d\n", datas->nb_philos);
	while (i < datas->nb_philos)
	{
		datas->pids[i] = fork();
		//printf("fork...\n");
		//printf("parents\n");
		//printf("datas->pids = %d\n", datas->pids[i]);
		if (datas->pids[i] == -1)
			exit(1);
		else if (!datas->pids[i])
		{
			//printf("childs...\n");
			//printf("datas->pids = %d\n", datas->pids[i]);
			exec_philo(datas, i);
			// free_datas
		}
		sleep(2);
		printf("datas->dead = %d\n", datas->dead);
		i++;
	}
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