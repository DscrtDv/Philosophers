#ifndef PHILO_H
# define PHILO_H
# define CDEAD		"\e[1;31m"
# define CEAT		"\e[1;32m"
# define CSLEEP		"\e[1;35m"
# define CTHINK		"\e[1;36m"
# define CRESET 	"\e[0m"
# define PHILO_MX	200
# define TIME_MIN	60
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stddef.h>
# include <stdbool.h>

//------ UTILS ------//
size_t	ft_strlen(const char *str);
long	ft_atoi(const char *nptr);

#endif