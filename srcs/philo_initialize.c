/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/02 19:30:59 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		monitoring_philos(t_philostatus *philo)
{
	int		index;

	index = 0;
	while (1)
	{
		philo[index].time_last_eat += get_time();
		philo_thinking(philo, philo[index].philo_id);
		if (philo[index].time_last_eat >= philo[index].time_must_eat)
			break ;
		if (philo[index].ammount_forks < 2)
			philo_steal_fork(philo, philo[index].philo_id);
		if (philo[index].ammount_forks == 2)
			philo_eating(philo, philo[index].philo_id);
		if (philo[index].has_eaten_status == 1)
			philo_sleeping(philo, philo[index].philo_id);
		index++;
		if (index > philo->mainstruct->number_of_philo)
			index = 0;
	}
	return (philo_died(philo, philo[index].philo_id));
}

void	*initialize_data_threads(void *data)
{
	t_philostatus	*philo;

	philo = data;
	philo->ammount_forks = 1;
	philo->time_must_eat = philo->mainstruct->time_to_die;
	philo->time_last_eat = 0;
	philo->dead_status = -1;
	philo->has_eaten_status = -1;
	monitoring_philos(philo);
	finishing_threads(philo);
	return (NULL);
}

int	initialize_threads(t_mainstruct *m_struct)
{
	int		index;

	index = 0;
	m_struct->philo_st = my_calloc(m_struct->number_of_philo, sizeof(t_philostatus));
	if (!m_struct->philo_st)
		return (-1);
	pthread_mutex_init(&m_struct->mutex_lock, NULL);
	while (index < m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index + 1;
		m_struct->philo_st[index].mainstruct = m_struct;
		pthread_create(&m_struct->threads[index], NULL, &initialize_data_threads, &(m_struct->philo_st[index]));
		index++;
	}
	return (1);
}
