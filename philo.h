/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:21:05 by dhussain          #+#    #+#             */
/*   Updated: 2023/05/10 14:56:06 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

struct s_mainstruct;

typedef struct s_philo_st {
	int					philo_id;
	long				start_time;
	int					ammount_forks;
	long				time_last_eat;
	long				time_must_eat;
	int					times_has_eaten;
	int					dead_status;
	int					has_eaten_status;
	struct s_mainstruct	*mainstruct;
}	t_philostatus;

typedef struct s_mainstruct {
	int					number_of_philo;
	int					number_of_threads;
	long				time_to_eat;
	long				time_to_die;
	long				time_to_sleep;
	long				ammount_of_eating;
	pthread_t 			*threads;
	pthread_mutex_t		mutex_lock;
	pthread_mutex_t		mutex_death_lock;
	struct s_philo_st	*philo_st;
}	t_mainstruct;

//Arguments
int		arg_checker(int argc, char *argv[]);
int		filling_struct(char *argv[], t_mainstruct *m_struct);
//Arguments Utils
int		my_atoi(char *str);
int		my_strlenght(char *str);
char	*my_strcpy(char *dest, const char *src);
int		my_is_digit(int c);
void	*my_calloc(size_t count, size_t size);

//Error and Free functions
int		error_print(char *str, t_mainstruct *m_struct);
void	free_struct(t_mainstruct *m_struct);

//Thread functions
int		initialize_threads(t_mainstruct *m_struct);

//Philo operations
int		philo_steal_fork(t_philostatus *philo, int philo_id);
int		philo_eating(t_philostatus *philo, int philo_id);
int		philo_thinking(t_philostatus *philo, int philo_id);
int		philo_sleeping(t_philostatus *philo, int philo_id);
int		philo_died(t_philostatus *philo, int philo_id);

//Utils
long	get_time(void);
void	sleeptight_function(t_philostatus *philo, long time);
void	finishing_threads(t_philostatus *philo);

#endif