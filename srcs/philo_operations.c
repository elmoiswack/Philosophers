/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:39 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/21 14:18:38 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	philo_steal_fork(t_philostatus *philo, int philo_id)
{
	pthread_mutex_lock(philo->left_fork);
	if (printing_action(philo, philo_id, "has taken a fork") == -1)
		return (-1);
	pthread_mutex_lock(philo->right_fork);
	if (printing_action(philo, philo_id, "has taken a fork") == -1)
		return (-1);
	philo_eating(philo, philo_id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	philo_eating(t_philostatus *philo, int philo_id)
{	
	pthread_mutex_lock(&philo->mainstruct->mutex_eating_lock);
	if (printing_action(philo, philo_id, "is eating") == -1)
		return (-1);
	sleeptight_function(philo, philo->mainstruct->time_to_eat);
	philo->current_time = get_time() - philo->start_time;
	philo->time_must_eat = philo->current_time + philo->mainstruct->time_to_die;
	philo->has_eaten_status = 1;
	philo->times_has_eaten += 1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_eating_lock);
	return (1);
}

int	philo_thinking(t_philostatus *philo, int philo_id)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_thinking_lock);
	if (printing_action(philo, philo_id, "is thinking") == -1)
		return (-1);
	pthread_mutex_unlock(&philo->mainstruct->mutex_thinking_lock);
	return (1);
}

int	philo_sleeping(t_philostatus *philo, int philo_id)
{
	pthread_mutex_lock(&philo->mainstruct->mutex_sleeping_lock);
	if (printing_action(philo, philo_id, "is sleeping") == -1)
		return (-1);
	sleeptight_function(philo, philo->mainstruct->time_to_sleep);
	pthread_mutex_unlock(&philo->mainstruct->mutex_sleeping_lock);
	return (1);
}

int	philo_died(t_philostatus *philo, int philo_id)
{
	// pthread_mutex_lock(&philo->mainstruct->mutex_death_lock);
	if (printing_action(philo, philo_id, "is dead") == -1)
		return (-1);
	// pthread_mutex_unlock(&philo->mainstruct->mutex_death_lock);
	return (1);
}