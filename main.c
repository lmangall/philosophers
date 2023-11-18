
#include "philo.h"

int	check_args(char **av) ///                 change the minimum ?
{
	if (ft_atoi(av[1]) == 1)
	{
		printf("%d 1 died\n", ft_atoi(av[2]));
		exit(1);
	}
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

// checks if any philo is dead or if all have eaten
void	*check_meals(void *data_pointer)
{
	t_data	*data;

	data = (t_data *)data_pointer;
	while (data->dead_phi == 0)
	{
		if (data->nb_ate == data->nb_philo)
		{
			pthread_mutex_lock(data->write);
			printf("All philosophers ate %d times\n", data->nb_eat);
			pthread_mutex_unlock(data->write);
			exit(1); //          FINISH   THE    PROGRAM
		}
		(void)data;
	}
	return (NULL);
}

void	a_table(t_data *data)
{
	int	i;
	int	threads_created;

	i = 0;
	threads_created = 0;
	if (data->nb_eat > 0)
		pthread_create(data->t0, NULL, check_meals, (void *)&data->philos[0]);
	while(i < data->nb_philo)
	{
		pthread_create(&data->threads[i], NULL, routine, &data->philos[i]);
		threads_created++;
		if (data->dead_phi == 1)
			break;		
		i++;
	}
	i = 0;
	while (i < threads_created)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	if (data->nb_eat > 0)
		pthread_join(*data->t0, NULL);
	if (data->dead_phi == 1)
		free_n_exit(data);
}

// write a fuction that free the memory and exits
void free_n_exit(t_data *data)
{
    int i;

    i = 0;

pthread_mutex_unlock(data->lock);
pthread_mutex_unlock(data->write);

    while (i < data->nb_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].lock);
        i++;
    }
    pthread_mutex_destroy(data->write);
    pthread_mutex_destroy(data->lock);
    free(data->forks);
    free(data->threads);
    free(data->philos);
    free(data->t0);
    free(data->lock);
    free(data->write);
    exit(1);
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
	init_data(&data, ac, av);
	init_forks(&data);
	init_philo(&data);
	a_table(&data);
	free_n_exit(&data);

	return (0);
}