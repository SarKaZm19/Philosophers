/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:44:34 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/24 21:14:49 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_err_msg(int errcode, char *str)
{
	if (errcode == 0)
		printf("Args format\n");
	else if (errcode == 1)
	{
		printf("syscall error :\n");
		perror(str);
	}

}

void	ft_error(t_data *datas, int errcode, char *str)
{
	datas->err_catch = 1;
	ft_err_msg(errcode, str);
	ft_free_datas(&datas);
}

int	usage_error(void)
{
	printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep"
		" [nb_time_each_philo_must_eat]");
	return (1);
}