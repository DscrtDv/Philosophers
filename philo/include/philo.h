/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 13:16:52 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/21 18:15:54 by tcensier      ########   odam.nl         */
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
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	int					n_philos;
	int					n_eat;
	int					*dead;
	int					eating;
	size_t				last_meal;
	size_t				t_die;
	size_t				t_eat;
	size_t				t_sleep;
	size_t				start_t;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*eat_lock;
}						t_philo;

typedef struct s_data
{
	int					death_flag;
	int					n_philos;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philos;
}						t_data;

//------ INIT -------//
void	init_data(t_data *data, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int n_philos);
void	init_philos(t_philo *philos, t_data *data, \
					pthread_mutex_t *forks, char **av);

//------ MONITOR ----//
void	*r_monitor(void *ptr);
void	print_msg(char *str, t_philo *philo, int id);

//------ THREADS ----//
int		create_threads(t_data *data, pthread_mutex_t *forks);
int		died_lock(t_philo *philo);
void	destroy_threads(char *str, t_data *data, pthread_mutex_t *forks);

//------ ROUTINES --//
void	r_think(t_philo *philo);
void	r_sleep(t_philo *philo);
void	r_eat(t_philo *philo);

//------ UTILS ------//
size_t	ft_strlen(const char *str);
long	ft_atoi(const char *nptr);
void	error_msg(char *msg, bool tutorial);
size_t	get_time(void);
int		f_usleep(size_t ms);

#endif