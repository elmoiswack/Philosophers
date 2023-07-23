/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:29:12 by dantehussai       #+#    #+#             */
/*   Updated: 2023/07/23 14:26:54 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	looping_operations(t_philostatus *philo)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	while (1)
	{
		philo->current_time = (get_time() - philo->mainstruct->start_time);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
			break ;
		philo_thinking(philo, philo->philo_id);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
			break ;
		philo_steal_fork(philo, philo->philo_id);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
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
		if (philo[index].current_time >= philo[index].time_must_eat)
		{
			philo->mainstruct->someone_died = 1;
			philo_died(philo, philo[index].philo_id);
			break ;
		}
		if (philo->mainstruct->everyone_is_full == 1)
			break ;
		index++;
		if (index == philo->mainstruct->number_of_philo)
			index = 0;
	}
	return (1);
}

int	one_philo_loop(t_philostatus *philo)
{
	int	boolean;

	boolean = 1;
	while (philo->current_time < philo->time_must_eat)
	{
		philo->current_time = (get_time() - philo->mainstruct->start_time);
		if (boolean == 1)
		{
			philo_thinking(philo, philo->philo_id);
			printing_action(philo, philo->philo_id, "has taken a fork");
			boolean = -1;
		}
	}
	return (1);
}
