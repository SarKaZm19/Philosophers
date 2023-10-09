/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:43:42 by fvastena          #+#    #+#             */
/*   Updated: 2023/10/09 15:46:22 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_datas(t_data **datas)
{
	/* printf("free_id...\n");
	if ((*datas)->id)
		free((*datas)->id); */
	printf("free_eating...\n");
	if ((*datas)->eating)
		free((*datas)->eating);
	printf("freeing count_eat... \n");
	if ((*datas)->count_eat)
		free((*datas)->count_eat);
	printf("freeing last_meal...\n");
	if ((*datas)->last_meal)
		free((*datas)->last_meal);
	printf("freeing philos...\n");
	if ((*datas)->philos)
		free((*datas)->philos);
	printf("freeing forks...\n");
	if ((*datas)->forks)
		free((*datas)->forks);
	printf("all freed\n");
}
