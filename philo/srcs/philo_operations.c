/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:39 by dhussain          #+#    #+#             */
/*   Updated: 2023/07/28 07:03:16 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	philo_steal_fork(t_philostatus *philo, int philo_id)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	pthread_mutex_lock(philo->left_fork);
	printing_action(philo, philo_id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printing_action(philo, philo_id, "has taken a fork");
	philo_eating(philo, philo_id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	philo_eating(t_philostatus *philo, int philo_id)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	pthread_mutex_lock(&philo->mainstruct->mutex_eating_lock);
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	philo->time_must_eat = philo->current_time + philo->mainstruct->time_to_die;
	philo->times_has_eaten += 1;
	if (philo->times_has_eaten == philo->mainstruct->ammount_of_eating)
		philo->mainstruct->philo_that_full += 1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	printing_action(philo, philo_id, "is eating");
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->philo_that_full \
		== philo->mainstruct->number_of_philo)
		philo->mainstruct->everyone_is_full = 1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	pthread_mutex_unlock(&philo->mainstruct->mutex_eating_lock);
	sleeptight_function(philo->mainstruct->time_to_eat, philo);
	return (1);
}

int	philo_thinking(t_philostatus *philo, int philo_id)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	pthread_mutex_lock(&philo->mainstruct->mutex_thinking_lock);
	printing_action(philo, philo_id, "is thinking");
	pthread_mutex_unlock(&philo->mainstruct->mutex_thinking_lock);
	return (1);
}

int	philo_sleeping(t_philostatus *philo, int philo_id)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	pthread_mutex_lock(&philo->mainstruct->mutex_sleeping_lock);
	printing_action(philo, philo_id, "is sleeping");
	pthread_mutex_unlock(&philo->mainstruct->mutex_sleeping_lock);
	sleeptight_function(philo->mainstruct->time_to_sleep, philo);
	return (1);
}

int	philo_died(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->mutex_death_lock);
	time = get_time() - philo->start_time;
	printf("%lu %i is dead\n", time, philo_id);
	pthread_mutex_unlock(&philo->mainstruct->mutex_death_lock);
	return (1);
}
