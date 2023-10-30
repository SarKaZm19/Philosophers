/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:56:51 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 00:55:30 by fvastena         ###   ########.fr       */
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

#include <inttypes.h> // print int64
typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_philo
{
	t_bool			is_dead;
	int				id;
	int				count_eat;
	int64_t			last_meal;
	pthread_t		thid;
	struct s_data	*datas;
}				t_philo;

typedef struct s_data
{
	t_bool			glob_dead;
	int				nb_philos;
	int				nb_meal;
	int				err_catch;
	int64_t			prog_start;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	t_philo			philos;
	pid_t			*pid;
	sem_t			*process;
	sem_t			*forks;
	sem_t			*lock;
}					t_data;

// srcs/processes/forks_bonus.c
void	drop_forks(t_data *datas);
void	take_forks(t_data *datas);

// srcs/processes/messages_bonus.c
void	messages(t_data *datas, char *str);

// srcs/processes/monitor_bonus.c
void	*monitor_fct(void *data_ptr);
int		end_cond(t_data *dt);

// srcs/structs/init_datas_bonus.c
int		init_datas(t_data *datas, int ac, char **av);
void	init_null(t_data *datas);

// srcs/structs/init_utils_bonus.c
void	verif_args(t_data *d);
int		ft_sem_init(t_data *datas);

// srcs/utils/errors_bonus.c
int		usage_error(void);
void	ft_error(t_data *datas, int errcode, char *str);

// srcs/utils/ft_free_datas.c
void	ft_free_datas(t_data **datas);
void	ft_destroy_semaphores(t_data *datas);

// srcs/utils/ft_atoi_bonus.c
int		ft_atoi(const char *nptr);

// srcs/utils/time_bonus.c
void	ft_usleep(uint64_t time);
int64_t gettime(void);


#endif