
#include "philo.h"

void	distrib_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->fork_l = (philo->id) % philo->data->nb_philo;
		philo->fork_r = philo->id - 1;
	}
	else
	{
		philo->fork_l = philo->id - 1;
		philo->fork_r = (philo->id) % philo->data->nb_philo;
	}
}


	void	init_philo(t_data *data)
	{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->philos = philo;
	while (i < (data->nb_philo))
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].eat_cont = 0;
		philo[i].eating = 0;
		philo[i].dead_or_alive = 1;
		philo[i].last_eat = data->start_time;
		philo[i].t1 = malloc(sizeof(pthread_t));
		philo[i].eat = malloc(sizeof(pthread_t));
		pthread_mutex_init(&philo->lock, NULL);
		i++;
	}
	}

void	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	if (ac == 6)
	{
		data->nb_eat = ft_atoi(av[5]);
	}
	else
		data->nb_eat = -1;
	data->nb_ate = 0;
	data->dead_phi = 0;
	data->finished = 0;
	data->thread_nbr = 0;
	data->threads = malloc(sizeof(int) * data->nb_philo);
	data->death_thread_id = 0;
	data->printed_end = 0;
	data->start_time = get_time() + (data->nb_philo * 2 * 10);
	data->tto_die = (u_int64_t)ft_atoi(av[2]);
	data->tto_eat = (u_int64_t)ft_atoi(av[3]);
	data->tto_sleep = (u_int64_t)ft_atoi(av[4]);
	data->death_thread = malloc(sizeof(pthread_t));
	data->meals = malloc(sizeof(pthread_t));
	data->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->lock, NULL);
	pthread_mutex_init(data->write, NULL);
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
	i = 0;
	while (i < data->nb_philo)
	{
		if (i % 2)
		{
			data->philos[i].fork_l = (i + 1) % data->nb_philo;
			data->philos[i].fork_r = i;
		}
		else
		{
			data->philos[i].fork_l = i;
			data->philos[i].fork_r = (i + 1) % data->nb_philo;
		}
		i++;
	}
}