

#include "philo.h"


typedef struct	s_data
{
	int	placeholder;

}	t_data;

void_init_data(t_data *data)
{
	data->placeholder = 0;
}


void *routine()
{
	while (1)
	{
		//take fork
		printf("timestamp_in_ms X has taken a fork\n");
		//eat
		printf("timestamp_in_ms X is eating\n");
		sleep
		printf("timestamp_in_ms X is sleeping\n");
		//think
		printf("timestamp_in_ms X is thinking\n");
	}
	return (NULL);

}

void init_philo(t_data *data)
{
	int i;
	pthread_t thread;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&thread, NULL, routine, NULL);
		pthread_detach(thread);
		i++;
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->tto_die = ft_atoi(av[2]);
	data->tto_eat = ft_atoi(av[3]);
	data->tto_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	init_philo(data);
}

int check_args(char **av)
{
	if (ft_atoi(av[1]) < 1)
		return (0);
	if (ft_atoi(av[2]) < 60)
		return (0);
	if (ft_atoi(av[3]) < 60)
		return (0);
	if (ft_atoi(av[4]) < 60)
		return (0);
	// if (ac == 6 && ft_atoi(av[5]) < 1)
	// 	return (0);
	return (1);
}


int	main(int ac, char **av)
{
		if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (!check_args(av))
	{
		printf("Error: wrong arguments\n");
		return (0);
	}

	t_data data;
	init_data(&data,ac,  av);

  return (0);
}