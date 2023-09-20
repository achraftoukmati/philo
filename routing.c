#include "philo.h"

void	thinking(t_philo *philo)
{
	printing("is thinking", philo);
	pthread_mutex_lock(philo->left_fork);
	printing("has taken a fork", philo);
	if (philo->n_philos == 1)
	{
		*philo->flag = 1;
		usleep(philo->tt_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printing("has taken a fork", philo);
	printing("is eating", philo);
	if (*philo->s == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	if (*philo->s == 0)
		usleep(philo->tt_eat * 1000);
}

void	sleeping(t_philo *philo)
{
	philo->time_now = get_time();
	*philo->flag = 1;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printing("is sleeping", philo);
	if (*philo->s == 0)
		usleep(philo->tt_sleep * 1000);
}

void	*routing(void *arg)
{
	t_philo	*data;

	data = arg;
	data->time_now = data->start;
	if (data->id % 2 == 0)
		usleep(data->tt_eat * 1000);
	while (*data->s == 0)
	{
		if (data->meals_n == data->meals_max && data->meals_max > 0)
			break ;
		thinking(data);
		if (data->n_philos == 1)
			break ;
		eating(data);
		sleeping(data);
		data->meals_n++;
	}
	return (NULL);
}
