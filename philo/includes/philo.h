/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:36:15 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/26 16:33:05 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <pthread.h> //thread functions
# include <unistd.h> //usleep
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX
# include <stdlib.h> // malloc
# include <string.h> // memset

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_philo
{
	t_bool			is_eating;
	int				id;
	int				count_eat;
	int64_t			last_meal;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_data	*datas;
}				t_philo;

typedef struct s_data
{
	t_bool			glob_dead;
	int				nb_philos;
	int				nb_meal;
	int				err_catch;
	int64_t			prog_start;
	int64_t			death_time;
	int64_t			eat_time;
	int64_t			pillow_time;
	t_philo			*philos;
	pthread_t		*thid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}					t_data;

//structs/init_datas.c
int			init_datas(t_data *datas, int ac, char **av);
void		init_null(t_data *datas);

//struct/init_utils.c
void		verif_args(t_data *d);
int			ft_mutex_init(t_data *datas);

// threads/forks.c
void		drop_forks(t_philo *ph);
void		take_forks(t_philo *ph);

// threads/messages.c
void		messages(t_philo *ph, char *str);

// thread/monitor.c
int			end_cond(t_data *dt);
void		monitor_fct(void *data_ptr);

//utils/errors.c
void		ft_error(t_data *datas, int errcode, char *str);
int			usage_error(void);

//utils/free.c
void		ft_destroy_mutexes(t_data **datas);
void		ft_free_datas(t_data **datas);

// utils/ft_atoi.c
int			ft_atoi(const char *s);

// utils/time.c
int64_t		gettime(void);
void		ft_usleep(uint64_t time);

#endif