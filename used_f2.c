#include "philo.h"

void	free_all(t_data *data)
{
	if (data->forks != NULL)
		free(data->forks);
	if (data->threads != NULL)
		free(data->threads);
	if (data->philos != NULL)
		free(data->philos);
}

int	dead_operation(t_data *input, t_philo *philo)
{
	unsigned long	last_meal;

	pthread_mutex_lock(&philo->meals_mutex);
	last_meal = get_time() - philo->time_now;
	pthread_mutex_unlock(&philo->meals_mutex);
	if (last_meal >= (unsigned long)input->t_die)
	{
		pthread_mutex_lock(&input->dead_mutex);
		input->dead = 1;
		pthread_mutex_unlock(&input->dead_mutex);
		pthread_mutex_lock(&input->print_mutex);
		printf("%ld %d died\n", last_meal, philo->id);
		pthread_mutex_unlock(&input->print_mutex);
		return (1);
	}
	return (0);
}

void	check_data(t_data *input)
{
	int	i;

	i = 0;
	while (input->dead == 0)
	{
		usleep(50);
		if (dead_operation(input, &input->philos[i]))
			break ;
		i++;
		if (i == input->n_philos)
			i = 0;
	}
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meals_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
}

int	not_dead(t_philo *philo)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->s == 1)
		ret = 0;
	pthread_mutex_unlock(philo->dead_mutex);
	return (ret);
}
