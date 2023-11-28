/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:13:43 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/28 20:43:59 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		error("Malloc error with the array of philos", data);
	data->philos = philo;
	while (++i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].eat_cont = 0;
		philo[i].last_eat = -1;
		philo[i].tto_eat = data->tto_eat;
		philo[i].t1 = (pthread_t *)malloc(sizeof(pthread_t));
		philo[i].eat = (pthread_t *)malloc(sizeof(pthread_t));
		philo[i].tto_die = data->tto_die;
		if (!philo[i].t1 || !philo[i].eat)
			error("Malloc error with a philo or eat thread", data);
		pthread_mutex_init(&philo[i].lock, NULL);
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	data->nb_ate = 0;
	data->dead_phi = 0;
	data->thread_nbr = 0;
	data->threads = malloc(sizeof(int) * data->nb_philo);
	if (!data->threads)
		error("Malloc error with threads", data);
	data->death_thread_id = 0;
	data->start_time = get_time();
	data->tto_die = ft_atoi(av[2]);
	data->tto_eat = ft_atoi(av[3]);
	data->tto_sleep = ft_atoi(av[4]);
	data->death_thread = malloc(sizeof(pthread_t));
	if (!data->death_thread)
		error("Malloc error with death_thread", data);
	data->meals = malloc(sizeof(pthread_t));
	if (!data->meals)
		error("Malloc error with meals", data);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead_phi_lock, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		error("Malloc error with forks", data);
	while (i < data->nb_philo && !(pthread_mutex_init(&data->forks[i], NULL)))
		i++;
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
