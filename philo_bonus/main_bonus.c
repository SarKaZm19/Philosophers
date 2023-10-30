/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:09:48 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/30 20:52:48 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	datas;
	int		i;

	if (ac < 5 || ac > 6)
		return (usage_error());
	if (init_datas(&datas, ac, av))
		return (1);
	if (processing(&datas))
		return (1);
	i = -1;
	while (++i < datas.nb_philos)
		sem_wait(datas.fed);
	kill_processes(&datas, datas.nb_philos);
	ft_destroy_semaphores(&datas);
	return (0);
}