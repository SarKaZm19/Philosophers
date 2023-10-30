/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:56:51 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 21:16:54 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h> // fork
# include <sys/types.h> //fork
# include <sys/time.h> // gettimeofday
# include <pthread.h> // threads
# include <fcntl.h> // semaphores
# include <sys/stat.h> // semaphores
# include <semaphore.h> // semaphores
# include <stdlib.h> // malloc
# include <limits.h> // INT_MAX
# include <string.h> // memset
# include <stdio.h> // printf
# include <sys/wait.h>//waitpid
# include <signal.h> //kill
# include <errno.h> //errno
# include <stdatomic.h> // atomic var

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_philo
{
	int				id;
	int				count_eat;
	atomic_int		last_meal;
	pthread_t		thid;
	int				pid;
	struct s_data	*datas;
}				t_philo;

typedef struct s_data
{
	int		nb_philos;
	int		nb_meal;
	int		err_catch;
	int		prog_start;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_philo	*philos;
	sem_t	*fed;
	sem_t	*forks;
	sem_t	*lock;
}					t_data;

// srcs/processes/forks_bonus.c
void	drop_forks(t_philo *philo);
void	take_forks(t_philo *philo);

// srcs/processes/messages_bonus.c
void	messages(t_philo *philo, char *str);

// srcs/processes/monitor_bonus.c
void	*monitor_fct(void *ph_arg);
void	kill_processes(t_data *datas, int max);

// srcs/processes/philos_bonus.c
int	processing(t_data *datas);

// srcs/structs/init_datas_bonus.c
int		init_datas(t_data *datas, int ac, char **av);
void	ft_destroy_semaphores(t_data *datas);

// srcs/utils/errors_bonus.c
int		usage_error(void);
void	ft_error(t_data *datas, int errcode, char *str);

// srcs/utils/ft_atoi_bonus.c
int		ft_atoi(const char *nptr);

// srcs/utils/time_bonus.c
void	ft_usleep(uint64_t time);
int gettime(void);

void	kill_processes(t_data *datas, int max);

#endif