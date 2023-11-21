/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 13:41:06 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/21 18:13:17 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_t;
	if (!died_lock(philo))
		printf("%zu %d %s\n" CRESET, time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	death_check(t_philo *philo, size_t t_die)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_time() - philo->last_meal >= t_die && !philo->eating)
		return (pthread_mutex_unlock(philo->eat_lock), 1);
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

int	death_search(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].n_philos)
	{
		if (death_check(&philos[i], philos[i].t_die))
		{
			print_msg(CDEAD "died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	fed_check(t_philo *philos)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	if (philos[0].n_eat == -1)
		return (0);
	while (i < philos[0].n_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].meals_eaten >= philos[0].n_eat)
			done++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (done == philos[0].n_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*r_monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
		if (death_search(philos) == 1 || fed_check(philos) == 1)
			break ;
	return (ptr);
}
