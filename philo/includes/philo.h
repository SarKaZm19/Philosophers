/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:15 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/03 16:37:07 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <pthread.h> //thread functions
# include <unistd.h> //usleep
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX
# include <stdlib.h> // ??
# include <string.h> // 

typedef enum
{
	FALSE,
	TRUE
}			bool;

typedef struct s_data
{
	bool			dead;
	int				nb_philos;
	int				id;
	int				nb_meal;
	int				*eating;
	int				*count_eat;
	__uint64_t		time_to_die;
	__uint64_t		time_to_eat;
	__uint64_t		time_to_sleep;
	__uint64_t 		time_start;
	__uint64_t		*last_meal;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data;

//structs/init_datas.c
void	init_null(t_data *datas);
void	init_datas(t_data *datas, int ac, char **av);

//structs/struct_utils.c


//utils/errors.c
int	usage_error(void);

//utils/free.c
void	ft_free_datas(t_data **datas);

// utils/ft_atoi.c
int	ft_atoi(const char *s);

// utils/time.c
__uint64_t gettime(void);
int	ft_usleep(__useconds_t time);

//mains.c
void	print_datas(t_data *datas);

#endif