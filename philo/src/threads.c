/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 14:54:29 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/21 18:15:43 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	died_lock(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static void	*r_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		f_usleep(1);
	while (!died_lock(philo))
	{
		r_eat(philo);
		r_sleep(philo);
		r_think(philo);
	}
	return (ptr);
}

void	destroy_threads(char *str, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->death_lock);
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, &r_monitor, data->philos) != 0)
		destroy_threads("Thread creation error: Monitor.", data, forks);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &r_philo,
				&data->philos[i]) != 0)
			destroy_threads("Thread creations error: Philos", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
		destroy_threads("Thread joining error: Monitor", data, forks);
	while (i < data->n_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_threads("Thread joining error: Philos", data, forks);
		i++;
	}
	return (EXIT_SUCCESS);
}
