
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

void a_table(t_data *data)
{
    int thread_nbr;

    thread_nbr = 0;
    while (thread_nbr < data->nb_philo)
    {
        pthread_create(data->philos[thread_nbr].t1, NULL, routine, &data->philos[thread_nbr]);
        thread_nbr++;
    }

    pthread_create(data->death_thread, NULL, check_death_or_meals, data);
    thread_nbr = 0;
    while (thread_nbr < data->nb_philo)
    {
        pthread_join(*(data->philos[thread_nbr].t1), NULL);
        thread_nbr++;
    }
    pthread_join(*(data->death_thread), NULL);
}

void free_n_exit(t_data *data)
{
printf("free_n_exit\n");
	int i;

	i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_unlock(&data->forks[i]);
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_unlock(&data->philos[i].lock);
        pthread_mutex_destroy(&data->philos[i].lock);
        i++;
    }
    pthread_mutex_unlock(data->write);
    pthread_mutex_destroy(data->write);
    pthread_mutex_unlock(data->lock);
    pthread_mutex_destroy(data->lock);
    free(data->forks);
    free(data->philos);
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
	init_philo(&data);
	init_forks(&data);
	a_table(&data);
	free_n_exit(&data);
	return (0);
}