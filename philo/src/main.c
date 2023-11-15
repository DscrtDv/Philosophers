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

#include "../include/philo.h"

bool arg_check(const char **av)
{
	if (ft_atoi(av[1]) > PHILO_MX || ft_atoi(av[1] <= 0))
		return (write(2, "Invalid amount of Philosophers.\n", 33), false);
	if (ft_atoi(av[2] < TIME_MIN))
		return (write(2, "Invalid death time limit.\n", 27), false);
	if (ft_atoi(av[3] < TIME_MIN))
		return (write(2, "Invalid eat duration.\n", 23), false);
	if (ft_atoi(av[4]) < TIME_MIN)
		return (write(2, "Invalid sleep duration.\n", 25), false);
	if (av[5] && (ft_atoi(av[5]) < 0))
		return (write(2, "Invalid number of times philosophers must eat.\n", 48), false);
	return (true);
}

int main (int ac, char **av)
{
	if (ac != 5 || ac != 6)
		return (write(2, "Invalid argument count. Please input 5 numerical arguments.\n", 61), EXIT_FAILURE);
	if (!arg_check(av))
		return (write(2, "Use:\n ./program {N_PHILO} {T_DEATH} {T_EAT} {T_SLEEP} {N_EAT_AMOUT}\n\t-N_PHILO <= 200\n\t-(T_DEATH, T_EAT, T_SLEEP) >= 60 (in ms)\n\t-N_EAT_AMOUT > 0 and optionnal\n", 160), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}