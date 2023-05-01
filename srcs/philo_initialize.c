/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/01 16:08:24 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		monitoring_philos(t_philostatus *philo)
{
	int		index;
	long	time;

	index = 0;
	while (1)
	{
		time = get_time();
		philo[index].time_last_eat += time;
		if (philo[index].time_last_eat >= philo[index].time_must_eat)
			break ;
		else if (philo[index].ammount_forks < 2)
			philo_steal_fork(philo, index);
		else if (philo[index].ammount_forks == 2)
			philo_eating(philo, index);
		else if (philo[index].sleeping_status == -1)
			philo_sleeping(philo, index);
		else if (philo[index].thinking_status == -1)
			philo_thinking(philo, index);
		index++;
		if (index > philo->mainstruct->number_of_philo)
			index = 0;
	}
	return (philo_died(philo, index));
}

void	*initialize_data_threads(void *data)
{
	t_philostatus	*philo;
	
	philo = data;
	philo->ammount_forks = 1;
	philo->time_must_eat = philo->mainstruct->time_to_eat;
	philo->time_last_eat = 0;
	philo->dead_status = -1;
	philo->eating_status = -1;
	philo->thinking_status = -1;
	philo->sleeping_status = -1;
	return (NULL);
}

int	initialize_threads(t_mainstruct *m_struct, pthread_t *threads)
{
	int	index;

	index = 0;
	m_struct->philo_st = my_calloc(m_struct->number_of_philo, sizeof(t_philostatus));
	if (!m_struct->philo_st)
		return (-1);
	while (index < m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index;
		pthread_create(&threads[index], NULL, &initialize_data_threads, &(m_struct->philo_st[index]));
		index++;
		m_struct->number_of_threads = index;
	}
	if (m_struct->number_of_threads != m_struct->number_of_philo)
		return (-1);
	return (1);
}
