/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:21:38 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/14 15:32:55 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_mainstruct *m_struct;

	if (arg_checker(argc, argv) == -1)
		return (error_print(("Error\nWrong arguments"), NULL));
	m_struct = (t_mainstruct *) malloc(1 * sizeof(t_mainstruct));
	if (!m_struct)
		return (error_print(("Error\nAllocation of struct failed"), NULL));
	filling_struct(argv, m_struct);
	if (m_struct->number_philo == -1)
	{
		free_struct(m_struct);
		return (-1);
	}
	initializing_threads(m_struct, argv);
	return (0);
}