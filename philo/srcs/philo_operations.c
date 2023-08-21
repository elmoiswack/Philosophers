/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:39 by dhussain          #+#    #+#             */
/*   Updated: 2023/08/21 05:40:53 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

int	philo_steal_fork(t_philostatus *philo, int philo_id)
{
	int	check;

	pthread_mutex_lock(philo->left_fork);
	printing_action(philo, philo_id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printing_action(philo, philo_id, "has taken a fork");
	check = philo_eating(philo, philo_id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (check);
}

int	philo_eating(t_philostatus *philo, int philo_id)
{
	if (printing_action(philo, philo_id, "is eating") == -1)
		return (-1);
	pthread_mutex_lock(&philo->mutex_eating);
	philo->time_must_eat = (get_time() - philo->mainstruct->start_time) \
		+ philo->mainstruct->time_to_die;
	philo->times_has_eaten += 1;
	pthread_mutex_unlock(&philo->mutex_eating);
	sleeptight_function(philo->mainstruct->time_to_eat, philo);
	return (1);
}

int	philo_thinking(t_philostatus *philo, int philo_id)
{
	if (printing_action(philo, philo_id, "is thinking") == -1)
		return (-1);
	return (1);
}

int	philo_sleeping(t_philostatus *philo, int philo_id)
{
	if (printing_action(philo, philo_id, "is sleeping") == -1)
		return (-1);
	sleeptight_function(philo->mainstruct->time_to_sleep, philo);
	return (1);
}

int	philo_died(t_philostatus *philo, int philo_id)
{
	long	time;

	pthread_mutex_lock(&philo->mainstruct->mutex_death_lock);
	time = get_time() - philo->mainstruct->start_time;
	printf("%lu %i is dead\n", time, philo_id);
	pthread_mutex_unlock(&philo->mainstruct->mutex_death_lock);
	return (1);
}
