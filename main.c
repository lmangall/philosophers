
#include "philo.h"

int check_args(char **av)///                 change the minimum ?
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

//checks if any philo is dead or if all have eaten
void	*check_meals(void *data_pointer)
{
// printf("control: check_death\n");

	t_data	*data = (t_data *)data_pointer;
	// int i;

	// i = 0;
	while(data->dead_phi == 0)
	//while (data->nb_ate < data->nb_philo && data->nb_eat != -1)//-1 means they don't have a nbr of time to eat
	{
		// if (get_time() - data->start_time - data->philos[i].last_eat > data->tto_die)
		// {
		// 	printf("XXX died\n");
		// 	printf("%llu %d died\n", get_time() - data->start_time, data->philos[i].id);
		// 	//exit (1);//          FINISH   THE    PROGRAM
		// }


		//check if any philo has eaten all his meals   => is this necessary ?
		if(data->nb_ate == data->nb_philo)
		{
			pthread_mutex_lock(data->write);
			printf("All philosophers ate %d times\n", data->nb_eat);
			exit (1);//          FINISH   THE    PROGRAM
			pthread_mutex_unlock(data->write);
		}

		// 	pthread_mutex_lock(data->lock);
		// if(data->dead_phi > 0)
		// {
		// 	printf("XXX died\n");
		// 	printf("%llu %d died\n", get_time() - data->start_time, data->philos[data->dead_phi].id);
		// 	exit (1);//          FINISH   THE    PROGRAM
		// }
		// if((data->nb_ate >= data->nb_eat) && (data->nb_eat != -1))
		// {
		// 		printf("All philosophers ate %d times\n", data->nb_eat);
		// 		exit (1);//          FINISH   THE    PROGRAM
		// }
		// pthread_mutex_unlock(data->lock);


		 (void)data;
		// i++;
	}
	return (NULL);
}


void	a_table(t_data *data)
{
// printf("control: a_table\n");
	int i;

	i = 0;

	//check for death
	if(data->nb_eat > 0)
		pthread_create(&data->t0, NULL, check_meals, &data->philos[0]);



	while (i < data->nb_philo)   //   CHANGE THIS
	// while(data->dead_phi == 0)
	{
		if (i % 2 == 0)
		 	usleep(1);
printf("-------- philo nbr %d (print from a_table()\n", i);
		pthread_create(&data->threads[i], NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
printf("-------- philo nbr %d JOINED (print from a_table()\n", i);
		pthread_join(data->threads[i], NULL);
		i++;
	}

	if(data->nb_eat > 0)
		pthread_join(data->t0, NULL);


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


  return (0);
}