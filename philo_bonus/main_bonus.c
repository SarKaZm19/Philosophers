/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:09:48 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 01:10:27 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

void	*monitor_fct(void *philo_arg)
{
	t_philo	*ph;
	int		i;

	ph = (t_philo *)philo_arg;
	while (1)
	{
/* 		sem_wait(dt->process);
		printf("id = %d\n", dt->philos.id);
		printf("count_eat = %d\n", dt->philos.count_eat);
		printf("coucou\n");
		sem_post(dt->process); */
		//printf("%p\n", &dt->philos.count_eat);
		if (ph->count_eat == ph->datas->nb_meal)
		{
			return (NULL);
		}
		if (gettime() - ph->last_meal >= ph->datas->time_to_die)
		{
			ph->is_dead = TRUE;
			sem_wait(ph->datas->lock);
			printf("%ld	%d died\n", gettime() - ph->datas->prog_start, ph->id);
			i = 0;
			while (i < ph->datas->nb_philos)
			{
				kill(ph->datas->pid[i], SIGINT);
				i++;
			}
			ft_destroy_semaphores(ph->datas);
			free(ph->datas->pid);
			exit(EXIT_FAILURE);
		}
/* 		else
		{
			printf("not dead\n");
		} */
		//ft_usleep(100);
		// usleep pour beaucoup de philo
	}
	return (NULL);
}

void	exec_philo(t_data *datas, int i)
{
	//printf("datas->philos.id = %d\n", datas->philos.id);
	t_philo	philo;

	philo.datas = datas;
	philo.id = i + 1;
	philo.is_dead = FALSE;
	philo.count_eat = 0;
	philo.last_meal = gettime();
/* 	if ((datas->philos.id & 1) == 0)
		ft_usleep(datas->time_to_eat / 2); */
	if (pthread_create(&philo.thid, NULL, &monitor_fct, (void *)&philo) != 0)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	while (datas->philos.is_dead == FALSE
		|| datas->philos.count_eat < datas->nb_meal)
	{
		take_forks(datas);
		messages(datas, "is eating");
		datas->philos.last_meal = gettime();
		ft_usleep(datas->time_to_eat);
		drop_forks(datas);
		messages(datas, "is sleeping");
		ft_usleep(datas->time_to_sleep);
		messages(datas, "is thinking");
		if (datas->nb_meal > 0)
			datas->philos.count_eat++;
	}
	if (pthread_join(datas->philos.thid, NULL) != 0)
	{
		perror("pthread_detach");
		exit(EXIT_FAILURE);
	}
}

void	processing(t_data *datas)
{
	int	i;

	i = 0;
	printf("hello test\n");
	while (i < datas->nb_philos)
	{
		datas->pid[i] = fork();
		if (datas->pid[i] == -1)
		{
			printf("failed ?\n");
			exit(1); // a protect
		}
		else if (!datas->pid[i])
		{
			exec_philo(datas, i);
			// free_datas
		}
		i++;
	}
	printf("hello test\n");
	i = -1;
	while (++i < datas->nb_philos)
	{
		waitpid(datas->pid[i], 0, 0);
	}
	i = -1;
	/* while (++i < datas->nb_philos)
		kill(datas->pid[i], SIGINT); */
	ft_destroy_semaphores(datas);
	//ft_free_datas(&datas);
}

int	main(int ac, char **av)
{
	t_data	datas;

	if (ac < 5 || ac > 6)
		return (usage_error());
	//printf("init_null...\n");
	//init_null(&datas);
	/* datas = malloc(sizeof(t_data));
	if (!datas)
		return (ft_error(datas, 1, "malloc"), 1); */
	//printf("init_datas...\n");
	init_datas(&datas, ac, av);
	//printf("threading...\n");

	processing(&datas);
	//printf("end...\n");

}