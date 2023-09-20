/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:54:56 by dhussain          #+#    #+#             */
/*   Updated: 2023/09/20 16:36:47 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	philo_that_full_check(t_philostatus *philo)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->philo_that_full \
		== philo->mainstruct->number_of_philo)
	{
		philo->mainstruct->everyone_is_full = 1;
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (-1);
}

int	monitoring_loop_philo(t_philostatus *philo, int index)
{
	while (index < philo->mainstruct->number_of_philo)
	{
		pthread_mutex_lock(&philo[index].mutex_eating);
		philo[index].current_time = get_time() - philo->mainstruct->start_time;
		if (philo[index].current_time > philo[index].time_must_eat)
		{
			pthread_mutex_lock(&philo->mainstruct->mutex_lock);
			philo->mainstruct->someone_died = 1;
			pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
			pthread_mutex_unlock(&philo[index].mutex_eating);
			philo_died(philo, philo[index].philo_id);
			return (1);
		}
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		if (philo[index].times_has_eaten == \
			philo->mainstruct->ammount_of_eating)
			philo->mainstruct->philo_that_full += 1;
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		pthread_mutex_unlock(&philo[index].mutex_eating);
		if (philo_that_full_check(philo) == 1)
			return (1);
		index++;
	}
	return (0);
}

void	monitoring_loop(t_philostatus *philo)
{
	if (philo->mainstruct->number_of_philo == 1)
		return ;
	while (1)
	{
		if (monitoring_loop_philo(philo, 0) == 1)
			return ;
		usleep(350 * 1000);
	}
	return ;
}
