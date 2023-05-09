/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:39 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/09 14:48:21 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	philo_steal_fork(t_philostatus *philo, int philo_id)
{
	long	time;
	
	if (philo[philo_id - 1].ammount_forks == 0 && philo[philo_id + 1].ammount_forks == 0)
		return (1);
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i has taken a fork\n", time, philo_id);
	philo->ammount_forks += 1;
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
	philo->time_last_eat += time;
	philo->time_must_eat = philo->time_last_eat + philo->mainstruct->time_to_die;
	philo->has_eaten_status = 1;
	philo->times_has_eaten += 1;
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
	philo->has_eaten_status = -1;
	printf("%lu %i is sleeping\n", time, philo_id);
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (1);
}

int	philo_died(t_philostatus *philo, int philo_id)
{
	long	time;
	int		index;

	index = 0;
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i died\n", time, philo_id);
	while (index < philo->mainstruct->number_of_philo)
	{
		pthread_mutex_lock(&philo->mainstruct->mutex_death_lock);
		philo[index].dead_status = 1;
		index++;
		pthread_mutex_unlock(&philo->mainstruct->mutex_death_lock);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	return (1);
}