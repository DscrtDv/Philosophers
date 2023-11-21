/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 13:57:00 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/21 18:13:28 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	r_think(t_philo *philo)
{
	print_msg(CTHINK "is thinking.", philo, philo->id);
}

void	r_sleep(t_philo *philo)
{
	print_msg(CSLEEP "is sleeping.", philo, philo->id);
	f_usleep(philo->t_sleep);
}

void	r_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(CEAT "has taken a fork.", philo, philo->id);
	if (philo->n_philos == 1)
	{
		f_usleep(philo->t_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_msg(CEAT "has taken a fork.", philo, philo->id);
	philo->eating = 1;
	print_msg(CEAT "is eating.", philo, philo->id);
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->eat_lock);
	f_usleep(philo->t_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
