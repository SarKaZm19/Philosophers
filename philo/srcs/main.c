/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:09 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/03 19:10:16 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_datas(t_data *datas)
{
	int	i;

	printf("is_dead = %d\n", datas->dead);
	printf("nb_philos = %d\n", datas->nb_philos);
	printf("id = %d\n", datas->id);
	printf("nb_meal = %d\n", datas->nb_meal);
	i = -1;
	while (++i < datas->nb_philos)
		printf("eating = %d\n", datas->eating[i]);
	i = -1;
	while (++i < datas->nb_philos)
		printf("count_eat = %d\n", datas->count_eat[i]);
	printf("time_to_die = %ld\n", datas->time_to_die);
	printf("time_to_eat = %ld\n", datas->time_to_eat);
	printf("time_to_sleep = %ld\n", datas->time_to_sleep);
	printf("time_start = %ld\n", datas->time_start);
	i = -1;
	while (++i < datas->nb_philos)
		printf("last_meal = %ld\n", datas->last_meal[i]);
	i = -1;
	while (++i < datas->nb_philos)
		printf("mutex_fork = %p\n", &datas->forks[i]);
	printf("mutex_lock = %p\n", &datas->lock);
	printf("mutex_write = %p\n", &datas->write);
}

void	messages(t_data *dt, int id, char *str)
{
	__uint64_t	time;

	pthread_mutex_lock(&dt->write);
	time = gettime() - dt->time_start;
	printf("%lu %d %s\n", time, id, str);
	pthread_mutex_unlock(&dt->write);
}

void	drop_forks(t_data *dt, int id)
{
	pthread_mutex_unlock(&dt->forks[id - 1]);
	//messages(philo, "dropped left fork");
	if (dt->nb_philos != 1)
	{
		if (id == dt->nb_philos)
			pthread_mutex_unlock(&dt->forks[0]);
		else
			pthread_mutex_unlock(&dt->forks[id]);
		//messages(philo, "dropped right fork");
	}
}

void	take_forks(t_data *dt, int id)
{
	pthread_mutex_lock(&dt->forks[id - 1]);
	messages(dt, id, "has taken left fork");
	if (dt->nb_philos != 1)
	{
		if (id == dt->nb_philos)
			pthread_mutex_lock(&dt->forks[0]);
		else
			pthread_mutex_lock(&dt->forks[id]);
		messages(dt, id, "has taken right fork");
	}
}

void	p_eating(t_data *dt, int id)
{
	take_forks(dt, id);
	messages(dt, id, "is eating");
	usleep(dt->time_to_eat * 1000);

	//dt->eating = TRUE;
	//ft_usleep(dt->time_to_eat);
	//dt->eating = FALSE;
	//dt->last_meal = gettime() - dt->time_start;
	drop_forks(dt, id);
	messages(dt, id, "is sleeping");
	usleep(dt->time_to_sleep * 1000);
	messages(dt, id, "is thinking");
}

void	*thread_function(void *datas_ptr)
{
	t_data 		*dt;
	static int	id;
	int			curr_id;

	dt = (t_data *)datas_ptr;
	pthread_mutex_lock(&dt->lock);
	id += 1;
	curr_id = id;
	pthread_mutex_unlock(&dt->lock);
	if (curr_id % 2 == 1)
		usleep((dt->time_to_eat / 2) * 1000);
	if (dt->nb_philos == 1)
	{
		printf("end\n");
	}
	else
		p_eating(dt, curr_id);
	return (NULL);
}

/* void	monitor(t_data *datas)
{
	while (datas->dead == FALSE)
	{
		
	}
} */

void	threading(t_data *datas)
{
	int	i = 0;
	datas->time_start = gettime();
	while (i < datas->nb_philos)
	{
		if (pthread_create(&(datas->philos[i]), NULL, &thread_function, datas) != 0)
		{
			perror("create");
			return ;
		}
		//ft_usleep(1);
		i++;
	}
	//monitor(datas);
	/* while (1)
	{
		if (datas->dead == TRUE)
			break ;
	} */
	i = 0;
	while (i < datas->nb_philos)
	{
		if (pthread_join(datas->philos[i], NULL) != 0)
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
		printf("init_null...\n");
		init_null(&datas);
		printf("init_datas...\n");
		init_datas(&datas, ac, av);
		printf("threading...\n");
		threading(&datas);
		printf("end...\n");
		//ministruct avec les data accessibles et le mutex dans la struct datas
		// + tableau de philo au lieu d'une struct ?
	}
	return (0);
}

void	time_test(void)
{
	struct timeval	start_time;
	struct timeval	end_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&start_time, NULL);

	printf("%ld\n", start_time.tv_sec);
	printf("%ld\n", start_time.tv_usec);
	int ret;
	char buf;
	while (1)
	{
		ret = read(0, &buf, 1);
		if (ret == -1)
			break ;
		if (buf == 'C')
			break;
	}
	gettimeofday(&end_time, NULL);
	gettimeofday(&end_time, NULL);
	if (end_time.tv_usec < start_time.tv_usec) {
        end_time.tv_sec--;
        end_time.tv_usec += 1000000; // 1 million (microseconds) to correct for overflow
    }
	printf("%ld\n", end_time.tv_sec - start_time.tv_sec);
	printf("%ld\n", end_time.tv_usec - start_time.tv_usec);
	time_t newtime_s;
	suseconds_t newtime_us;
	newtime_s = end_time.tv_sec - start_time.tv_sec; 
	newtime_us = end_time.tv_usec - start_time.tv_usec;
	printf("time elapsed = %ld,%ld\n", newtime_s, newtime_us);
}