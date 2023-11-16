/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 13:16:52 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/16 13:42:45 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define CDEAD		"\e[1;31m"
# define CEAT		"\e[1;32m"
# define CSLEEP		"\e[1;35m"
# define CTHINK		"\e[1;36m"
# define CERR		"\e[1;33m"
# define CRESET 	"\e[0m"
# define ERR		"[ERROR]"
# define PHILO_MX	200
# define TIME_MIN	60
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_data
{
	bool				death_flag;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		think_lock;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	int					n_philos;
	int					n_eat;
	bool				*dead;
	bool				eating;
	size_t				last_meal;
	size_t				t_die;
	size_t				t_eat;
	size_t				t_sleep;
	size_t				t_start;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*think_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*eat_lock;
}						t_philo;

//------ UTILS ------//
size_t	ft_strlen(const char *str);
long	ft_atoi(const char *nptr);
void	error_msg(char *msg, bool tutorial);

#endif

// Args:
// number_of_philosophers 	<= 200
// time_to_die				>= 60ms
// time_to_eat				>= 60ms
// time_to_sleep			>= 60ms
// number_of_times_each_philosopher_must_eat

//FORMAT
// timestamp_ms X has taken a fork
// timestamp_ms X is eating
// timestamp_ms X is sleeping
// timestamp_ms X is thinking
// timestamp_ms X died
