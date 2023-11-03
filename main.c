

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}


void	eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->forks[philo->id]);
	pthread_mutex_lock(&data->forks[philo->id + 1]);
	philo->status = EATING;
	philo->eat_cont++;
	printf("%llu %d is eating\n", get_time() - data->start_time, philo->id);
	usleep(data->tto_eat * 1000);// Since there are 1000 microseconds in a millisecond, you can multiply tto_eat by 1000 to achieve the desired delay in microseconds.
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[philo->id + 1]);
}

void	sleep(t_data *data, t_philo *philo)
{
	philo->status = SLEEPING;
	printf("%llu %d is sleeping\n", get_time() - data->start_time, philo->id);
	usleep(data->tto_sleep * 1000);
}

void	think(t_data *data, t_philo *philo)
{
	philo->status = THINKING;
	printf("%llu %d is thinking\n", get_time() - data->start_time, philo->id);
}

void *routine(t_data *data, t_philo *philo)
{
	//check_death(data, philo);
	while (1)
	{
		eat(data, philo);
		sleep(data, philo);
		think(data, philo);
	}
}



void init_philo(t_data *data)
{
	int i;
	pthread_t thread;

	printf("init_philo\n");

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&thread, NULL, routine, NULL);
		pthread_detach(thread);
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->lock, NULL);
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