
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



/*



				WHAT JOIN DO AND WHEN TO DO IT ?

have a mutex on the print, so two don't print in the same time


*/

//checks if a philo is dead or if he has eaten all his meals
// void	*check_death(void *philo_pointer)
// {
// // printf("control: check_death\n");

// 	t_philo	*philo = (t_philo *)philo_pointer;


// 	while(philo->dead_or_alive == 1)
// 	{
// 		pthread_mutex_lock(&philo->lock);
// 		if (get_time() - philo->last_eat > philo->data->tto_die)
// 		{
// 			printf("%llu %d died\n", get_time() - philo->data->start_time, philo->id);
// 			//exit (1);//          FINISH   THE    PROGRAM
// 		}
// 		if ((philo->eat_cont >= philo->data->nb_eat) && (philo->data->nb_eat != -1))
// 		{
// 			pthread_mutex_lock(philo->data->lock);
// 			philo->data->nb_ate++;
// 			pthread_mutex_unlock(philo->data->lock);
// 			if (philo->data->nb_ate == philo->data->nb_philo)
// 			{
// 				printf("All philosophers ate %d times\n", philo->data->nb_eat);
// 				//return (1);//          FINISH   THE    PROGRAM
// 			}
// 			philo->eat_cont = -1;//This means that this philo has eaten all his meals
// 		}
// 		pthread_mutex_unlock(&philo->lock);
		
// 	}
// 	return (NULL);
// }

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
	// if(data->nb_eat != -1)
	// 	pthread_create(&data->t0, NULL, check_meals, &data->philos[0]);

	while (i < data->nb_philo)   //   CHANGE THIS
	{
// printf("control: a_table while\n");
		if (i % 2 == 0)
			usleep(100);
		pthread_create(&data->threads[i], NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
// printf("control: a_table while\n");
		pthread_join(data->threads[i], NULL);
		i++;
	}

	// if(data->nb_eat != -1)
	// 	pthread_join(data->t0, NULL);


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