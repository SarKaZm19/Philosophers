/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:44:34 by fvastena          #+#    #+#             */
/*   Updated: 2023/09/29 22:44:44 by fvastena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usage_error(void)
{
	printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep"
		" [nb_time_each_philo_must_eat]");
	return (1);
}