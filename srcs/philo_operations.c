/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:39 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/02 19:01:16 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	philo_steal_fork(t_philostatus *philo, int philo_id)
{
	long	time;
	
	if (philo[philo_id - 1].ammount_forks < 1 && philo[philo_id + 1].ammount_forks < 1)
		return (1);
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i has taken a fork\n", time, philo_id);
	philo[philo_id].ammount_forks = 2;
	if (philo[philo_id + 1].ammount_forks > 0)
		philo_id++;
	else
		philo_id--;
	if (philo_id > philo->mainstruct->number_of_philo)
		philo_id = 0;
	philo[philo_id].ammount_forks -= 1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (1);
}

int	philo_eating(t_philostatus *philo, int philo_id)
{	
	long	time;
	
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i is eating\n", time, philo_id);
	philo[philo_id].time_last_eat += time;
	philo[philo_id].time_must_eat = philo[philo_id].time_last_eat + philo[philo_id].mainstruct->time_to_die;
	philo[philo_id].has_eaten_status = 1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (1);
}

int	philo_thinking(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i is thinking\n", time, philo_id);
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (1);
}

int	philo_sleeping(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	philo[philo_id].has_eaten_status = -1;
	printf("%lu %i is sleeping\n", time, philo_id);
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (1);
}

int	philo_died(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i died\n", time, philo_id);
	philo->dead_status = 1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (1);
}