/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 14:26:13 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/21 18:09:50 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_input(t_philo *philo, char **av)
{
	philo->n_philos = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->n_eat = ft_atoi(av[5]);
	else
		philo->n_eat = -1;
}

void	init_forks(pthread_mutex_t *forks, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philos(t_philo *philos, t_data *data, \
					pthread_mutex_t *forks, char **av)
{
	int	i;
	int	n_philo;

	i = 0;
	n_philo = ft_atoi(av[1]);
	data->n_philos = n_philo;
	while (i < n_philo)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_input(&philos[i], av);
		philos[i].start_t = get_time();
		philos[i].last_meal = get_time();
		philos[i].dead_lock = &data->death_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].eat_lock = &data->eat_lock;
		philos[i].dead = &data->death_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[n_philo - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_data(t_data *data, t_philo *philos)
{
	data->death_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
}
