/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:29:12 by dantehussai       #+#    #+#             */
/*   Updated: 2023/05/22 11:37:51 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	looping_operations(t_philostatus *philo)
{
	while (1)
	{
		if (philo->mainstruct->someone_died == 1)
			break ;
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		philo->current_time += get_time();
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		if (philo->mainstruct->someone_died == 1)
			break ;
		philo_thinking(philo, philo->philo_id);
		if (philo->mainstruct->someone_died == 1)
			break ;
		philo_steal_fork(philo, philo->philo_id);
		if (philo->mainstruct->someone_died == 1)
			break ;
		if ((philo->mainstruct->ammount_of_eating != -1) && (philo->times_has_eaten == philo->mainstruct->ammount_of_eating))
			break ;
		philo_sleeping(philo, philo->philo_id);
	}
	return (0);
}

int	monitoring_loop(t_philostatus *philo)
{
	int	index;

	index = 0;
	while (1)
	{
		if ((philo[index].current_time - philo[index].start_time) >= philo[index].time_must_eat)
		{
			philo->mainstruct->someone_died = 1;
			philo_died(philo, philo->philo_id);
			break ;
		}
		if ((philo->mainstruct->ammount_of_eating != -1) && (philo->times_has_eaten == philo->mainstruct->ammount_of_eating))
			return (1);
		index++;
		if (index == philo->mainstruct->number_of_philo)
			index = 0;
	}
	return (1);
}