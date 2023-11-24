
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


// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;

// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(time / 10);
// 	return (0);
// }

void	a_table(t_data *data)
{
	int	thread_nbr;

	thread_nbr = 0;
	while(thread_nbr < data->nb_philo)
	{
		pthread_create(&data->philos[thread_nbr].t1, NULL, routine, &data->philos[thread_nbr]);
		thread_nbr++;
	}
	data->thread_nbr = thread_nbr;
	printf("      thread_nbr: %d\n", thread_nbr);
	pthread_mutex_lock(data->lock);
	data->death_thread_id = 0;
	pthread_mutex_unlock(data->lock);
	pthread_create(data->death_thread, NULL, check_death_or_meals, data);
}

//important: the mutex is unlocked before being destroyed

void join_threads(t_data *data) 
{
	int i;

	i = 0;
    while (i < data->thread_nbr) 
	{
        if (data->threads[i] != -1) 
		{
            pthread_join(data->philos[i].t1, NULL);
			data->threads[i] = -1;
        }
		i++;
    }
}


void free_n_exit(t_data *data)
{
printf("free_n_exit\n");
	data->thread_nbr--;
	// ft_usleep(10);
if (data->thread_nbr == 0)
	{
			printf("freeing all\n");

		int i;

		i = 0;
		join_threads(data);
	printf("joined all threads\n");

		if(data->death_thread_id == 1)
		{
			pthread_join(*data->death_thread, NULL);
			data->death_thread_id = 0;
			printf("death thread joined\n");
		}
		i = 0;
		
		while (i < data->nb_philo)
		{
printf("  in while, i = %d\n", i);
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
		//free(data->threads);
		free(data->philos);
		//free(data->t0);
		free(data->lock);
		free(data->write);
		exit(1);
	}
	else
	{
		printf("freeing all = next time\n");
		ft_usleep(100);
	}

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
	ft_usleep(1000000);
	return (0);
}