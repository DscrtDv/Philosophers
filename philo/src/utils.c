/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 13:17:02 by tcensier      #+#    #+#                 */
/*   Updated: 2023/12/04 16:54:50 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	ft_atoi(const char *nptr)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while (*nptr && (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

int	f_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(ms / 10);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		error_msg("Get time failed.\n", false);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	error_msg(char *msg, bool tutorial)
{
	printf(CERR "[ERROR]" CRESET);
	if (msg)
		printf(" %s", msg);
	if (tutorial)
		printf("./philo {N_PHILO} {TIME_TO_DEATH} \
		{TIME_TO_EAT} {TIME_TO_SLEEP} {N_TIMES_TO_EAT}\n");
}
