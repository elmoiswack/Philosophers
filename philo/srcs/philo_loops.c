/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:29:12 by dantehussai       #+#    #+#             */
/*   Updated: 2023/07/31 17:10:59 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	looping_operations(t_philostatus *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(250);
	while (1)
	{
		if (philo_thinking(philo, philo->philo_id) == -1)
			break ;
		if (philo_steal_fork(philo, philo->philo_id) == -1)
			break ;
		if (philo_sleeping(philo, philo->philo_id) == -1)
			break ;
	}
	return (0);
}

int	monitoring_loop_philo(t_philostatus *philo, int index)
{
	while (index < philo->mainstruct->number_of_philo)
	{
		pthread_mutex_lock(&philo[index].mutex_must_eating);
		philo[index].current_time = get_time() - philo->mainstruct->start_time;
		if (philo[index].current_time > philo[index].time_must_eat)
		{
			pthread_mutex_lock(&philo->mainstruct->mutex_lock);
			philo->mainstruct->someone_died = 1;
			pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
			pthread_mutex_unlock(&philo[index].mutex_must_eating);
			philo_died(philo, philo[index].philo_id);
			return (-1);
		}
		if (philo->mainstruct->philo_that_full == philo->mainstruct->number_of_philo)
		{
			pthread_mutex_lock(&philo->mainstruct->mutex_lock);
			philo->mainstruct->everyone_is_full = 1;
			pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
			pthread_mutex_unlock(&philo[index].mutex_must_eating);
			return (-1);
		}
		pthread_mutex_unlock(&philo[index].mutex_must_eating);
		index++;
	}
	return (0);
}

int	monitoring_loop(t_philostatus *philo)
{
	int	index;

	index = 0;
	if (philo->mainstruct->number_of_philo == 1)
		return (1);
	while (1)
	{
		if (monitoring_loop_philo(philo, 0) == -1)
			return (1);
		usleep(250);
	}
	return (1);
}

int	one_philo_loop(t_philostatus *philo)
{
	int		boolean;
	long	time;
	long	time_wait;
	
	time = get_time() - philo->mainstruct->start_time;
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time_wait = philo->time_must_eat;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	boolean = 1;
	while (time_wait > time)
	{
		time = get_time() - philo->mainstruct->start_time;
		if (boolean == 1)
		{
			philo_thinking(philo, philo->philo_id);
			printing_action(philo, philo->philo_id, "has taken a fork");
			boolean = -1;
		}
	}
	printf("%lu %i is dead\n", time, philo->philo_id);
	return (1);
}
