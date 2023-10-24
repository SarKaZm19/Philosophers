/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:56:51 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/19 14:33:24 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h> // fork
# include <sys/types.h> //fork
# include <sys/time.h> // gettimeofday
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <stdlib.h>
# include <limits.h>

# include <stdio.h>

typedef enum
{
	FALSE,
	TRUE
}			bool;

typedef struct s_data
{
	bool	dead;
	int		nb_philos;
	int		nb_meal;
	int		*count_eat;
	pid_t			*pids;
	sem_t 			*f_lock;
	sem_t			*w_lock;
	sem_t			*e_lock;
	__uint64_t		time_to_die;
	__uint64_t		time_to_eat;
	__uint64_t		time_to_sleep;
	__uint64_t 		time_start;
	__uint64_t		*last_meal;
}				t_data;

// srcs/structs/init_datas_bonus.c
void	init_datas(t_data *datas, int ac, char **av);
void	init_null(t_data *datas);

// srcs/utils/errors_bonus.c
int		usage_error(void);

// srcs/utils/ft_atoi_bonus.c
int	ft_atoi(const char *nptr);

// srcs/utils/time_bonus.c
int	ft_usleep(__useconds_t time);
__uint64_t gettime(void);


#endif