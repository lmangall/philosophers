
#include "philo.h"

void init_philo(t_data *data)
{
printf("control: init_philo, nb_philo: %d\n", data->nb_philo);
printf("time: %llu\n", (get_time() - data->start_time));

	int i;
	//pthread_t thread;
	t_philo *philo;


	philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	//data->tid = malloc(sizeof(pthread_t) * data->nb_philo);
	data->start_time = get_time();
	i = 1;
	while (i < data->nb_philo)
	{
printf("control: init_philo while\n");
		philo[i].id = i;
		philo[i].eat_cont = 0;
		philo[i].status = THINKING;
		philo[i].data = data;
		philo[i].dead_or_alive = 1;
		philo[i].last_eat = get_time();
		pthread_mutex_init(&philo[i].lock, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		//pthread_create(&data->tid[i], NULL, routine, &philo[i]);//pass the data struct ?
		i++;
	}
	//i = 0;
	//while (i < data->nb_philo)
	//{
	//	pthread_join(data->tid[i], NULL);
	//	i++;
	//}
}

// void	init_mutex(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		pthread_mutex_init(&data->forks[i], NULL);
// 		i++;
// 	}
// 	pthread_mutex_init(&data->lock, NULL);
// }

void	init_data(t_data *data, int ac, char **av)
{
printf("control: init_data\n");

	data->nb_philo = ft_atoi(av[1]);
	data->tto_die = (u_int64_t) ft_atoi(av[2]);
	data->tto_eat = ft_atoi(av[3]);
	data->tto_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	data->tid = malloc(sizeof(pthread_t) * data->nb_philo);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	data->start_time = get_time();
	
	//init_mutex(data);
}

/*

	data->tto_die = (u_int64_t) ft_atoi(argv[2]);

}*/