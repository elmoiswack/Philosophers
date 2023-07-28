/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:29:12 by dantehussai       #+#    #+#             */
/*   Updated: 2023/07/28 06:43:21 by dantehussai      ###   ########.fr       */
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
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		philo->current_time = (get_time() - philo->start_time);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
		{
			pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		philo_thinking(philo, philo->philo_id);
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
		{
			pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		philo_steal_fork(philo, philo->philo_id);
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		if ((philo->mainstruct->someone_died == 1) \
			|| (philo->mainstruct->everyone_is_full == 1))
		{
			pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
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
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		if (philo[index].current_time >= philo[index].time_must_eat)
		{
			pthread_mutex_lock(&philo->mainstruct->mutex_death_lock);
			philo->mainstruct->someone_died = 1;
			pthread_mutex_unlock(&philo->mainstruct->mutex_death_lock);
			philo_died(philo, philo[index].philo_id);
			pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
			break ;
		}
		if (philo->mainstruct->everyone_is_full == 1)
			break ;
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
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
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		philo->current_time = (get_time() - philo->start_time);
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		if (boolean == 1)
		{
			philo_thinking(philo, philo->philo_id);
			printing_action(philo, philo->philo_id, "has taken a fork");
			boolean = -1;
		}
	}
	return (1);
}
