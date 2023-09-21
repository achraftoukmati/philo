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

int	check_data(t_data *input)
{
	t_philo *philo ;
	int	i;
	unsigned long last_meal;
	i = 0;
	while (input->dead == 0)
	{	
			usleep(input->t_eat * 100);
			philo = &input->philos[i];
			pthread_mutex_lock(&philo->meals_mutex);
			last_meal = get_time() - input->philos[i].time_now;
			pthread_mutex_unlock(&philo->meals_mutex);
			if ( last_meal >= (unsigned long)input->t_die)
			{
				pthread_mutex_lock(&input->dead_mutex);
				input->dead = 1;
				pthread_mutex_unlock(&input->dead_mutex);	
				pthread_mutex_lock(&input->print_mutex);
				printf("%ld %d died\n", last_meal, philo->id);
				pthread_mutex_unlock(&input->print_mutex);
				return (0);
			}
			i++;
			if (i == input->n_philos)
				i = 0;
	}
	return (0);
}

int	error(t_data *data, char *msg)
{
	int	i;

	i = 0;
	free_all(data);
	while (msg[i] != '\0')
	{
		write(2, &msg[i], 1);
		i++;
	}
	return (EXIT_FAILURE);
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

int not_dead(t_philo *philo)
{
	int ret;
	ret = 1;
	pthread_mutex_lock(philo->dead_mutex);
		if(*philo->s == 1)
			ret = 0;
	pthread_mutex_unlock(philo->dead_mutex);
	return(ret);
}
