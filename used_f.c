#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sing;
	int	rest;
	int	i;

	i = 0;
	sing = 1;
	rest = 0;
	while ((str[i] == '\f' || str[i] == '\t'
			|| str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sing *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		rest = rest * 10 + str[i++] - '0';
	return (rest * sing);
}

int	ft_isdigit(int d)
{
	if (d >= 48 && d <= 57)
		return (1);
	return (0);
}

int	ft_space(char c)
{
	if (c == '\f' || c == '\t' || c == ' ' || c == '\n' || c == '\r'
		|| c == '\v')
		return (1);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
