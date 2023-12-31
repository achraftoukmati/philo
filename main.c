#include "philo.h"

int	check_input(t_data *input)
{
	if ((input->food_access <= 0 && input->food_access != NO_PAR)
		|| input->n_philos <= 0 || input->t_die <= 0 || input->t_eat <= 0
		|| input->t_sleep <= 0)
		return (0);
	return (1);
}

int	check_string(char *s)
{
	int	i;

	i = 0;
	while (ft_space(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]))
		{
			while (ft_space(s[i]))
				i++;
			if (s[i] != '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_input_chars(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
	{
		if (!check_string(av[i]))
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
		pthread_mutex_init(&input->print_mutex, NULL);
		pthread_mutex_init(&input->dead_mutex, NULL);
		return (check_input(input));
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
