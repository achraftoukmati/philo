#include "philo.h"

int	check_input(t_data *input)
{
	if ((input->food_access <= 0 && input->food_access != NO_PAR)
		|| input->n_philos <= 0 || input->t_die <= 0 || input->t_eat <= 0
		|| input->t_sleep <= 0)
		return (0);
	return (1);
}

int	check_input_chars(int ac, char **av)
{
	int	i;
	int	j;
	int	d;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
	{
		j = 0;
		d = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]) && !ft_space(av[i][j]))
				return (0);
			if (ft_isdigit(av[i][j]))
				d++;
			j++;
		}
		if (d == 0)
			return (0);
		i++;
	}
	return (1);
}

int	get_data(t_data *input, int ac, char **av)
{
	if (check_input_chars(ac, av))
	{
		input->n_philos = ft_atoi(av[1]);
		input->t_die = ft_atoi(av[2]);
		input->t_eat = ft_atoi(av[3]);
		input->t_sleep = ft_atoi(av[4]);
		if (ac == 6)
			input->food_access = ft_atoi(av[5]);
		else
			input->food_access = NO_PAR;
		input->dead = 0;
		input->meals_n = 0;
		input->flag = 0;
		return (check_input(input));
	}
	return (0);
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

int	main(int ac, char **av)
{
	t_data	input;

	if (get_data(&input, ac, av))
	{
		if (start_threads(&input))
			return (error(&input, "err:\nerror while starting threads\n"));
		check_data(&input);
		if (wait_threads(&input))
			return (error(&input, "err:\nerror while joining threads\n"));
		mutex_destroy(&input);
		free_all(&input);
		return (EXIT_SUCCESS);
	}
	else
	{
		write(2, "err:\ninvalid args\n", 19);
		return (EXIT_FAILURE);
	}
}
