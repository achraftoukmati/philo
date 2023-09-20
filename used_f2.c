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
	int	i;

	i = 0;
	while (input->dead == 0)
	{
		if (input->flag == 1)
		{
			if (get_time()
				- input->philos[i].time_now >= (unsigned long)input->t_die)
			{
				input->dead = 1;
				printf("%ld %d died\n", (get_time()
						- input->philos[i].time_now), input->philos[i].id);
				return (0);
			}
			i++;
			if (i == input->n_philos)
				i = 0;
		}
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
		i++;
	}
}
