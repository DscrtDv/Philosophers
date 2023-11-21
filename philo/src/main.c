/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 13:16:40 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/21 18:11:23 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	num_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool	arg_check(char **av)
{
	if (ft_atoi(av[1]) > PHILO_MX || ft_atoi(av[1]) <= 0 || !num_check(av[1]))
		return (error_msg("Invalid amount of Philosophers. \
						Input between 1 and 200\n", false), false);
	if (ft_atoi(av[2]) < TIME_MIN || !num_check(av[2]))
		return (error_msg("Invalid death time limit.\
						 Minimum = 60ms\n", false), false);
	if (ft_atoi(av[3]) < TIME_MIN || !num_check(av[3]))
		return (error_msg("Invalid eat duration.\
						 Minimum = 60ms\n", false), false);
	if (ft_atoi(av[4]) < TIME_MIN || !num_check(av[4]))
		return (error_msg("Invalid sleep duration.\
						 Minimum = 60ms\n", false), false);
	if (av[5] && ((ft_atoi(av[5]) < 0) || !num_check(av[5])))
		return (error_msg("Invalid number of times philosophers must eat.\
						 Minimum = 1\n", false), false);
	return (true);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philos[PHILO_MX];
	pthread_mutex_t	forks[PHILO_MX];

	if (ac != 5 && ac != 6)
		return (error_msg("Invalid argument count.\n", true), EXIT_FAILURE);
	if (!arg_check(av))
		return (EXIT_FAILURE);
	init_data(&data, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, &data, forks, av);
	create_threads(&data, forks);
	destroy_threads(NULL, &data, forks);
	return (EXIT_SUCCESS);
}
