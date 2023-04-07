/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:21:05 by dhussain          #+#    #+#             */
/*   Updated: 2023/04/06 11:04:58 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_mainstruct {
	int		number_philo;
}	t_mainstruct;

//Arguments
int		arg_checker(int argc, char *argv[]);
//Arguments Utils
int		my_atoi(char *str);
int		my_is_digit(int c);

//Error and Free functions
int		error_print(char *str);
void	free_struct(t_mainstruct *m_struct);

//Philo operations
void	philo_eating();
void	philo_thinking();
void	philo_sleeping();

#endif