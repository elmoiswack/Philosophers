/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:29:12 by dantehussai       #+#    #+#             */
/*   Updated: 2023/07/11 16:19:35 by dantehussai      ###   ########.fr       */
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
		if (philo->current_time == -1)
			return (-1);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
			break ;
		if (philo_thinking(philo, philo->philo_id) == -1)
			return (-1);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
			break ;
		if (philo_steal_fork(philo, philo->philo_id) == -1)
			return (-1);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
			break ;
		if (philo_sleeping(philo, philo->philo_id) == -1)
			return (-1);
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
			if (philo_died(philo, philo[index].philo_id) == -1)
				return (-1);
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
			if (philo_thinking(philo, philo->philo_id) == -1)
				return (-1);
			if (printing_action(philo, philo->philo_id, "has taken a fork") == -1)
				return (-1);
			boolean = -1;
		}
	}
	return (1);
}