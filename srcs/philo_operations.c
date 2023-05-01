/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:39 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/01 16:06:00 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int	philo_steal_fork(t_philostatus *philo, int philo_id)
{
	long	time;
	
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i has taken a fork\n", time, philo_id);
	philo[philo_id].ammount_forks = 2;
	philo_id++;
	if (philo_id == philo->mainstruct->number_of_philo)
		philo_id = 0;
	philo[philo_id].ammount_forks -= 1;
}

int	philo_eating(t_philostatus *philo, int philo_id)
{	
	long	time;
	
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i is eating\n", time, philo_id);
	philo->time_last_eat = philo->time_last_eat + time;
	philo->time_must_eat = philo->time_must_eat + philo->mainstruct->time_to_eat;
}

int	philo_thinking(t_philostatus *philo, int philo_id)
{
	long	time;
	
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i is thinking\n", time, philo_id);
}

int	philo_sleeping(t_philostatus *philo, int philo_id)
{
	long	time;
	
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i is sleeping\n", time, philo_id);
}

int	philo_died(t_philostatus *philo, int philo_id)
{
	long	time;
	
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%lu %i died\n", time, philo_id);
	philo->dead_status = 1;
	return (1);
}