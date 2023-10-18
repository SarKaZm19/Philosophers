/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:09 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/18 19:57:33 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_datas(t_data *datas);


//faire autre fonction pour monitorer le temps entre deux repas, dans main ? loop, si temps gettime() - last_meal > death_time --> dead
void	p_eating(t_philo *ph)
{
	uint64_t	curr_time;

	take_forks(ph);
	//usleep(dt->time_to_eat * 1000);
	pthread_mutex_lock(&ph->datas->lock);
	curr_time = gettime() - ph->last_meal;
	pthread_mutex_lock(&ph->dead_m);
	ph->is_eating = TRUE;
	pthread_mutex_lock(&ph->datas->glob_dead_m);
 	if (curr_time > ph->datas->death_time && ph->is_eating == FALSE)
	{
		ph->datas->glob_dead = TRUE;
		pthread_mutex_unlock(&ph->datas->glob_dead_m);
		messages(ph, "is dead");
		ph->is_dead = TRUE;
		pthread_mutex_unlock(&ph->dead_m);
		pthread_mutex_unlock(&ph->datas->lock);
		return ;
	}
	pthread_mutex_unlock(&ph->datas->glob_dead_m);
	pthread_mutex_unlock(&ph->dead_m);
	pthread_mutex_unlock(&ph->datas->lock);
	ph->last_meal = gettime();
	messages(ph, "is eating");
	ft_usleep(ph->time_to_eat);
	ph->is_eating = FALSE;
	drop_forks(ph);
	messages(ph, "is sleeping");
	//usleep(dt->time_to_sleep * 1000);
	ft_usleep(ph->time_to_sleep);
}

void	*thread_function(void *ph_ptr)
{
	t_philo		*ph;

	ph = (t_philo *)ph_ptr;
	if ((ph->id & 1) == 0)
		ft_usleep(1);
	while (1)
	{	
		pthread_mutex_lock(&ph->datas->glob_dead_m);
		if (ph->datas->glob_dead == TRUE)
		{
			pthread_mutex_unlock(&ph->datas->glob_dead_m);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->datas->glob_dead_m);
		p_eating(ph);
		pthread_mutex_lock(&ph->datas->glob_dead_m);
		if (ph->datas->glob_dead == TRUE)
		{
			pthread_mutex_unlock(&ph->datas->glob_dead_m);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->datas->glob_dead_m);
		messages(ph, "is thinking");
	}
	return (NULL);
}

void	threading(t_data *datas)
{
	int	i = 0;
	datas->prog_start = gettime();
	printf("prog_start = %llu\n", datas->prog_start);
	while (i < datas->nb_philos)
	{
		datas->philos[i].last_meal = datas->prog_start;
		if (pthread_create(&(datas->thid[i]), NULL, &thread_function, &datas->philos[i]) != 0)
		{
			perror("create");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < datas->nb_philos)
	{
		if (pthread_join(datas->thid[i], NULL) != 0)
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
	printf("mutex_lock = %p\n", &datas->lock);
	printf("mutex_write = %p\n", &datas->write);
	while (++i < datas->nb_philos)
		printf("forks[%d] = %p\n", i, &datas->forks[i]);
	i = -1;
	while (++i < datas->nb_philos)
	{
		printf("id = %d\n", datas->philos[i].id);
		printf("is_dead = %d\n", datas->philos[i].is_dead);
		printf("is_eating = %d\n", datas->philos[i].is_eating);
		printf("count_eat = %d\n", datas->philos[i].count_eat);
		printf("time_to_die = %llu\n", datas->philos[i].time_to_die);
		printf("time_to_eat = %llu\n", datas->philos[i].time_to_eat);
		printf("time_to_sleep = %llu\n", datas->philos[i].time_to_sleep);
		printf("last_meal = %llu\n", datas->philos[i].last_meal);
		printf("r_fork = %p\n", datas->philos[i].r_fork);
		printf("l_fork = %p\n", datas->philos[i].l_fork);
		printf("dead_m = %p\n", &datas->philos[i].dead_m);
	}

}
