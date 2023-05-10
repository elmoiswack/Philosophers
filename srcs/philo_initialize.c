/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:10:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/10 16:52:46 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		monitoring_philos(t_philostatus *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mainstruct->mutex_lock);
		philo->time_last_eat += get_time();
		pthread_mutex_unlock(&philo->mainstruct->mutex_lock);
		if ((philo->time_last_eat - philo->start_time >= philo->time_must_eat) || (philo->dead_status == 1))
			;
		philo_thinking(philo, philo->philo_id);
		if (philo->ammount_forks < 2)
			philo_steal_fork(philo, philo->philo_id);
		if (philo->ammount_forks == 2)
			philo_eating(philo, philo->philo_id);
		if (philo->mainstruct->ammount_of_eating != -1 && philo->times_has_eaten == philo->mainstruct->ammount_of_eating)
			;
		philo_sleeping(philo, philo->philo_id);
	}
	if (philo->dead_status != 1)
		philo_died(philo, philo->philo_id);
	return (0);
}

void	*initialize_data_threads(void *data)
{
	t_philostatus	*philo;

	philo = data;
	philo->ammount_forks = 1;
	philo->start_time = get_time();
	philo->time_must_eat = philo->mainstruct->time_to_die;
	philo->times_has_eaten = 0;
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

	index = 1;
	m_struct->philo_st = my_calloc(m_struct->number_of_philo, sizeof(t_philostatus));
	if (!m_struct->philo_st)
		return (-1);
	pthread_mutex_init(&m_struct->mutex_lock, NULL);
	pthread_mutex_init(&m_struct->mutex_death_lock, NULL);
	while (index <= m_struct->number_of_philo)
	{
		m_struct->philo_st[index].philo_id = index;
		m_struct->philo_st[index].mainstruct = m_struct;
		pthread_create(&m_struct->threads[index], NULL, &initialize_data_threads, &(m_struct->philo_st[index]));
		index++;
		usleep(250);
	}
	return (1);
}
