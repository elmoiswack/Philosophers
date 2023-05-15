/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:39 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/15 15:55:24 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	philo_steal_fork(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->left_fork);
	time = get_time();
	if (time == -1)
		return (-1);
	time = time - philo->start_time;
	pthread_mutex_lock(&philo->right_fork);
	time = get_time();
	if (time == -1)
		return (-1);
	time = time - philo->start_time;
	printf("%lu %i is taken a fork\n", time, philo_id);
	philo_eating(philo, philo_id);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (1);
}

int	philo_eating(t_philostatus *philo, int philo_id)
{	
	long	time;
	
	pthread_mutex_lock(&philo->mainstruct->mutex_eating_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	time = time - philo->start_time;
	printf("%lu %i is eating\n", time, philo_id);
	sleeptight_function(philo, philo->mainstruct->time_to_eat);
	philo->time_last_eat += time;
	philo->time_must_eat = philo->time_last_eat + philo->mainstruct->time_to_die;
	philo->has_eaten_status = 1;
	philo->times_has_eaten += 1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_eating_lock);
	return (1);
}

int	philo_thinking(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->mutex_thinking_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	time = time - philo->start_time;
	printf("%lu %i is thinking\n", time, philo_id);
	pthread_mutex_unlock(&philo->mainstruct->mutex_thinking_lock);
	return (1);
}

int	philo_sleeping(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->mutex_sleeping_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	philo->has_eaten_status = -1;
	time = time - philo->start_time;
	printf("%lu %i is sleeping\n", time, philo_id);
	sleeptight_function(philo, philo->mainstruct->time_to_sleep);
	printf("nani de kanker\n");
	pthread_mutex_unlock(&philo->mainstruct->mutex_sleeping_lock);
	return (1);
}

int	philo_died(t_philostatus *philo, int philo_id)
{
	long	time;
	int		index;

	index = 0;
	pthread_mutex_lock(&philo->mainstruct->mutex_death_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	time = time - philo->start_time;
	printf("%lu %i died\n", time, philo_id);
	pthread_mutex_unlock(&philo->mainstruct->mutex_death_lock);
	return (1);
}