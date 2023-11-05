
#include "philo.h"

// void	print_data(t_data *data)
// {
// 	printf("data->nb_philo: %d\n", data->nb_philo);
// 	printf("data->tto_die: %llu\n", data->tto_die);
// 	printf("data->tto_eat: %llu\n", data->tto_eat);
// 	printf("data->tto_sleep: %llu\n", data->tto_sleep);
// 	printf("data->nb_eat: %d\n", data->nb_eat);
// 	printf("data->start_time: %llu\n", data->start_time);
// 	printf("data->nb_ate: %d\n", data->nb_ate);
// 	printf("data->forks: %p\n", (void *)data->forks);
// 	printf("data->lock: %p\n", (void *)data->lock);
// 	printf("data->philos: %p\n", (void *)data->philos);
// 	printf("data->t1: %p\n", (void *)data->t1);
// }

void init_philo(t_data *data)
{
printf("control: init_philo, nb_philo: %d\n", data->nb_philo);
// printf("time: %llu\n", (get_time() - data->start_time));

	int i;
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->philos = philo; // Store the pointer in data->philos
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->start_time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
// printf("control: init_philo while\n");
		philo[i].id = i;
		philo[i].eat_cont = 0;
		// philo[i].status = THINKING;
		philo[i].data = data;
		philo[i].dead_or_alive = 1;
		philo[i].last_eat = 0;
		// pthread_mutex_init(&philo[i].eat, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		pthread_mutex_init(&philo[i].write, NULL);
		i++;
	}
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
	data->nb_philo = ft_atoi(av[1]);
	data->tto_die = (u_int64_t) ft_atoi(av[2]);
	data->tto_eat = (u_int64_t) ft_atoi(av[3]);
	data->tto_sleep = (u_int64_t) ft_atoi(av[4]);
	if (ac == 6)
	{
		data->nb_eat = ft_atoi(av[5]);
		printf("data->nb_eat: %d\n", data->nb_eat);
	}
	else
		data->nb_eat = -1;
	data->nb_ate = 0;
	data->dead_phi = 0;
	data->t0 = malloc(sizeof(pthread_t));	
	data->threads = malloc(sizeof(pthread_t) * data->nb_philo);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	data->start_time = get_time();
	data->lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->lock, NULL);	
	//print_data(data);
}

void	init_forks(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}





/*

	data->tto_die = (u_int64_t) ft_atoi(argv[2]);

}*/