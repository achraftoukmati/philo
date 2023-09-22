#include "philo.h"

void	philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->n_philos = data->n_philos;
	philo->start = get_time();
	philo->tt_die = data->t_die;
	philo->tt_eat = data->t_eat;
	philo->tt_sleep = data->t_sleep;
	philo->meals_n = 0;
	philo->time_now = 0;
	philo->flag = &data->flag;
	philo->s = &data->dead;
	philo->meals_max = data->food_access;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->n_philos];
	philo->dead_mutex = &data->dead_mutex;
	philo->print_mutex = &data->print_mutex;
	pthread_mutex_init(&philo->meals_mutex, NULL);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (data->philos == NULL)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (data->forks == NULL)
		return (1);
	data->threads = malloc(sizeof(pthread_t) * data->n_philos);
	if (data->threads == NULL)
		return (1);
	while (i < data->n_philos)
	{
		philo(&data->philos[i], data, i);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

void	printing(char *s, t_philo *data)
{
	if (not_dead(data))
	{
		pthread_mutex_lock(data->print_mutex);
		printf("%ld %d %s\n", (get_time() - data->start), data->id, s);
		pthread_mutex_unlock(data->print_mutex);
	}
}

int	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->threads[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	start_threads(t_data *data)
{
	int	i;

	if (init_philos(data))
		return (1);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &routing, &data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}
