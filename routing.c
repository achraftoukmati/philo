#include "philo.h"

void	thinking(t_philo *philo)
{
	printing("is thinking", philo);
	pthread_mutex_lock(philo->left_fork);
	printing("has taken a fork", philo);
	if (philo->n_philos == 1)
	{
		usleep(philo->tt_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printing("has taken a fork", philo);
	printing("is eating", philo);
	if (not_dead(philo))
		usleep(philo->tt_eat * 1000);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printing("is sleeping", philo);
	if (not_dead(philo))
		usleep(philo->tt_sleep * 1000);
}

void	*routing(void *arg)
{
	t_philo	*data;

	data = arg;
	pthread_mutex_lock(&data->meals_mutex);
	data->time_now = data->start;
	pthread_mutex_unlock(&data->meals_mutex);
	if (data->id % 2 == 0)
		usleep(100);
	while (not_dead(data))
	{
		if (data->meals_n == data->meals_max && data->meals_max > 0)
			break ;
		thinking(data);
		if (data->n_philos == 1)
			break ;
		eating(data);	
		pthread_mutex_lock(&data->meals_mutex);
		data->time_now = get_time();
		pthread_mutex_unlock(&data->meals_mutex);
		sleeping(data);
		// check_data(data->data_ptr);
		data->meals_n++;
		// if(not_dead(data))
		// 	check_data(data->data_ptr);
	}
	return (NULL);
}
