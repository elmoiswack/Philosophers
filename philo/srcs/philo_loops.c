/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:29:12 by dantehussai       #+#    #+#             */
/*   Updated: 2023/09/28 13:56:16 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	looping_operations_uneven(t_philostatus *philo)
{
	while (1)
	{
		if (philo_sleeping(philo, philo->philo_id) == -1)
			break ;
		if (philo_thinking(philo, philo->philo_id) == -1)
			break ;
		if (philo_steal_fork(philo, philo->philo_id) == -1)
			break ;
	}
	return (0);
}

int	looping_operations_even(t_philostatus *philo)
{
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

void	*which_thread_loop(void	*data)
{
	t_philostatus	*philo;

	philo = data;
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->thread_failed == 1)
	{
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	if (philo->mainstruct->number_of_philo == 1)
		one_philo_loop(philo);
	else
	{
		if (philo->philo_id % 2 == 0)
			looping_operations_even(philo);
		else
			looping_operations_uneven(philo);
	}
	return (NULL);
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
