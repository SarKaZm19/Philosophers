/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:09 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/11 19:14:18 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_datas(t_data *datas);

void	p_eating(t_philo *ph)
{
	take_forks(ph);
	messages(ph, "is eating");
	//usleep(dt->time_to_eat * 1000);
	ph->last_meal = gettime() - ph->time_start;
 	if (ph->last_meal > ph->time_to_die)
	{
		printf("coucou mort\n");
		ph->is_dead = TRUE;
		messages(ph, "is dead");
		return ;
	}
	ph->is_eating = TRUE;
	ft_usleep(ph->time_to_eat);
	ph->is_eating = FALSE;
	drop_forks(ph);
	messages(ph, "is sleeping");
	//usleep(dt->time_to_sleep * 1000);
	ft_usleep(ph->time_to_sleep);
	messages(ph, "is thinking");
}

int	check_state(t_data *datas)
{
	/* uint64_t	elapsed;

	elapsed = gettime() - datas->time_start;
	while (elapsed > datas->time_to_die && datas->eating[datas->id] == FALSE)
	{
		elapsed += gettime() - datas->last_meal[datas->id];
		datas->id_dead = datas->id;
		datas->dead = TRUE;
		return (0);
	}
	return (1); */
	/* pthread_mutex_lock(&datas->lock);
	if (datas->dead == TRUE)
	{
		printf("dead\n");
		pthread_mutex_unlock(&datas->lock);
		return (0);
	}
	pthread_mutex_unlock(&datas->lock);
	return (1); */
	(void)datas;
	return (0);
		
}

void	*thread_function(void *ph_ptr)
{
	t_philo		*ph;

	ph = (t_philo *)ph_ptr;
	if ((ph->id & 1) == 0)
		ft_usleep(100);
	p_eating(ph);
	return (NULL);
}

/* void	monitor(t_data *datas)
{
	while (1)
	{
		if (datas->dead == TRUE)
		{
			pthread_mutex_lock(&datas->write);
			messages(datas, id, "died");
			pthread_mutex_unlock(&datas->write);
			break ;
		}
	}
} */

/* int	exit_philos(t_data *datas)
{
	int	i;

	i = -1;
	while (++i < datas->nb_philos)
	{
		pthread_mutex_unlock(&datas->forks[i]);
	}
	i = -1;
	while (++i < datas->nb_philos)
	{
		pthread_mutex_unlock(&datas->forks[i]);
		if (pthread_detach(datas->philos[i]) != 0)
		{
			perror("joining");
			return (1);
		}
	}
	ft_free_datas(&datas);
	return (0);
} */

void	threading(t_data *datas)
{
	int	i = 0;
	datas->prog_start = gettime();
	while (i < datas->nb_philos)
	{
		datas->philos[i].time_start = datas->prog_start;
		if (pthread_create(&(datas->philos[i].th_p), NULL, &thread_function, &datas->philos[i]) != 0)
		{
			perror("create");
			return ;
		}
		i++;
	}
/* 	while (1)
	{
		check_state(datas);
		printf("state = %d\n", datas->dead);
		if (datas->dead == TRUE)
		{
			pthread_mutex_lock(&datas->dead_mt);
			printf("coucou dead\n");
			messages(datas, datas->id_dead, "is dead");
			exit_philos(datas);
			pthread_mutex_unlock(&datas->dead_mt);
			return ;
		}
	} */
	//monitor(datas);

	i = 0;
	while (i < datas->nb_philos)
	{
		if (pthread_join(datas->philos[i].th_p, NULL) != 0)
		{
			perror("joining");
			return ;
		}
		i++;
	}
	printf("freeing datas...\n");
	ft_free_datas(&datas);
}


void	time_test(void);
// add -pthread at compilation
int main(int ac, char **av)
{
	t_data			datas;

	//time_test();
	if (ac < 5 || ac > 6)
		return (usage_error());
	else
	{
		//printf("init_null...\n");
		init_null(&datas);
		//printf("init_datas...\n");
		init_datas(&datas, ac, av);
		//printf("threading...\n");
		threading(&datas);
		printf("end...\n");
		//ministruct avec les data accessibles et le mutex dans la struct datas
		// + tableau de philo au lieu d'une struct ?
	}
	return (0);
}

void	print_datas(t_data *datas)
{
	int	i;

	printf("is_dead = %d\n", datas->glob_dead);
	printf("nb_philos = %d\n", datas->nb_philos);
	printf("nb_meal = %d\n", datas->nb_meal);
	printf("prog_start = %llu\n", datas->prog_start);
	i = -1;
	while (++i < datas->nb_philos)
	{
		printf("id = %d\n", datas->philos[i].id);
		printf("is_dead = %d\n", datas->philos[i].is_dead);
		printf("is_eating = %d\n", datas->philos[i].is_eating);
		printf("count_eat = %d\n", datas->philos[i].count_eat);
		printf("th_p = %p\n", &datas->philos[i].th_p);
		printf("time_to_die = %llu\n", datas->philos[i].time_to_die);
		printf("time_to_eat = %llu\n", datas->philos[i].time_to_eat);
		printf("time_to_sleep = %llu\n", datas->philos[i].time_to_sleep);
		printf("time_start = %llu\n", datas->philos[i].time_start);
		printf("last_meal = %llu\n", datas->philos[i].last_meal);
		printf("r_fork = %p\n", &datas->philos[i].r_fork);
		printf("l_fork = %p\n", &datas->philos[i].l_fork);
		printf("p_lock = %p\n", &datas->philos[i].p_lock);
		printf("p_write = %p\n", &datas->philos[i].p_write);
	}
	printf("mutex_lock = %p\n", &datas->lock);
	printf("mutex_write = %p\n", &datas->write);
}
