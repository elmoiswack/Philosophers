/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:21:38 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/10 14:20:42 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_mainstruct	*m_struct;

	if (arg_checker(argc, argv) == -1)
		return (error_print(("Error\nWrong arguments"), NULL));
	m_struct = (t_mainstruct *)my_calloc(1, sizeof(t_mainstruct));
	if (!m_struct)
		return (error_print(("Error\nAllocation of struct failed"), NULL));
	filling_struct(argv, m_struct);
	m_struct->threads = (pthread_t *)malloc(m_struct->number_of_philo * sizeof(pthread_t));
	if (!m_struct->threads)
		return (error_print(("Error\nAllocation of struct failed"), m_struct));
	if (initialize_threads(m_struct) == -1)
		return (error_print(("Error\nA thread failed"), m_struct));
	return (0);
}