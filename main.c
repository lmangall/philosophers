
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
int	check_death(t_philo *philo)
{
	while(philo->dead_or_alive == 1)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() - philo->last_eat > philo->data->tto_die)
		{
			printf("%llu %d died\n", get_time() - philo->data->start_time, philo->id);
			return (1);//          FINISH   THE    PROGRAM
		}
		if ((philo->eat_cont >= philo->data->nb_eat) && (philo->data->nb_eat != -1))
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->nb_ate++;
			pthread_mutex_unlock(&philo->data->lock);
			if (philo->data->nb_ate == philo->data->nb_philo)
			{
				printf("All philosophers ate %d times\n", philo->data->nb_eat);
				return (1);//          FINISH   THE    PROGRAM
			}
			philo->eat_cont = -1;//This means that this philo has eaten all his meals
		}
		pthread_mutex_unlock(&philo->lock);
		
	}
	return (0);
}

void	a_table(t_data *data)
{
	int i;

	i = 1;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].t1, NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].t1, NULL);
		i++;
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
	init_philo(&data);
	a_table(&data);


  return (0);
}