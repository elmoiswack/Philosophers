/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/19 16:47:58 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	looping_operations(t_philostatus *philo)
{
	while (1)
	{
		if (philo->mainstruct->someone_died == 1)
			break ;
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		philo->current_time += get_time();
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		if (philo->mainstruct->someone_died == 1)
			break ;
		philo_thinking(philo, philo->philo_id);
		if (philo->mainstruct->someone_died == 1)
			break ;
		philo_steal_fork(philo, philo->philo_id);
		if (philo->mainstruct->someone_died == 1)
			break ;
		if ((philo->mainstruct->ammount_of_eating != -1) && (philo->times_has_eaten == philo->mainstruct->ammount_of_eating))
			break ;
		philo_sleeping(philo, philo->philo_id);
	}
	return (0);
}

int	monitoring_loop(t_philostatus *philo)
{
	int	index;

	index = 0;
	while (1)
	{
		if ((philo[index].current_time - philo[index].start_time) >= philo[index].time_must_eat)
		{
			philo_died(philo, philo->philo_id);
			philo->mainstruct->someone_died = 1;
			break ;
		}
		if ((philo->mainstruct->ammount_of_eating != -1) && (philo->times_has_eaten == philo->mainstruct->ammount_of_eating))
			return (1);
		index++;
		if (index == philo->mainstruct->number_of_philo)
			index = 0;
	}
	return (1);
}

void	*initialize_data_threads(void *data)
{
	t_philostatus	*philo;

	philo = data;
	pthread_mutex_lock(&philo->mainstruct->mutex_lock);
	fork_initialize(philo, philo->philo_id - 1);
	philo->start_time = get_time();
	philo->time_must_eat = philo->mainstruct->time_to_die;
	philo->times_has_eaten = 0;
	philo->current_time = 0;
	philo->dead_status = -1;
	philo->has_eaten_status = -1;
	pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
	if (philo->philo_id % 2 == 0)
		usleep(250);
	looping_operations(philo);
	finishing_threads(philo);
	return (NULL);
}

int	initialize_mutexes(t_mainstruct *m_struct)
{
	if (pthread_mutex_init(&m_struct->mutex_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_eating_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_sleeping_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_thinking_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&m_struct->mutex_death_lock, NULL) == -1)
		return (-1);
	return (1);
}

int	initialize_threads(t_mainstruct *m_struct)
{
	int		index;

	index = 0;
	m_struct->philo_st = malloc(m_struct->number_of_philo * sizeof(t_philostatus));
	if (!m_struct->philo_st)
		return (-1);
	if (initialize_mutexes(m_struct) == -1)
		return (-1);
	m_struct->forks = malloc(m_struct->number_of_philo * sizeof(pthread_mutex_t));
	if (!m_struct->forks)
		return (-1);
	m_struct->someone_died = -1;
	while (index < m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index + 1;
		m_struct->philo_st[index].mainstruct = m_struct;
		pthread_create(&m_struct->threads[index], NULL, &initialize_data_threads, &(m_struct->philo_st[index]));
		index++;
		usleep(250);
	}
	monitoring_loop(m_struct->philo_st);
	return (1);
}
