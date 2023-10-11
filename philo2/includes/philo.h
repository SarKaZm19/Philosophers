/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:15 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/11 18:59:59 by fvastena         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	bool			is_dead;
	bool			is_eating;
	int				count_eat;
	pthread_t		th_p;
	__uint64_t		time_to_die;
	__uint64_t		time_to_eat;
	__uint64_t		time_to_sleep;
	__uint64_t 		time_start;
	uint64_t		last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*p_lock;
	pthread_mutex_t	*p_write;
	struct s_data	*datas;
}				t_philo;

typedef struct s_data
{
	bool			glob_dead;
	int				nb_philos;
	int				nb_meal;
	uint64_t		prog_start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data;

//structs/init_datas.c
void	init_null(t_data *datas);
void	init_datas(t_data *datas, int ac, char **av);

//structs/struct_utils.c

// threads/forks.c
void	drop_forks(t_philo *ph);
void	take_forks(t_philo *ph);

// threads/messages.c
void	messages(t_philo *ph, char *str);

//utils/errors.c
int	usage_error(void);

//utils/free.c
void	ft_free_datas(t_data **datas);

// utils/ft_atoi.c
int	ft_atoi(const char *s);

// utils/time.c
__uint64_t gettime(void);
void	ft_usleep(uint64_t time);
void	time_test(void);

//mains.c
void	print_datas(t_data *datas);

#endif