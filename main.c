/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:14:01 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/26 14:16:41 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av)
{
	if (ft_atoi(av[1]) == 1)
	{
		printf("%d 1 died\n", ft_atoi(av[2]));
		exit(1);
	}
	if (ft_atoi(av[1]) < 1)
		return (0);
	if (ft_atoi(av[2]) < 1)
		return (0);
	if (ft_atoi(av[3]) < 1)
		return (0);
	if (ft_atoi(av[4]) < 1)
		return (0);
	return (1);
}

void	a_table(t_data *data)
{
	int	thread_nbr;

	thread_nbr = 0;
	if (data->nb_eat != -1)
		pthread_create(data->meals, NULL, check_all_ate, data);
	while (thread_nbr < data->nb_philo)
	{
		pthread_create(data->philos[thread_nbr].t1, NULL, routine,
			&data->philos[thread_nbr]);
		pthread_create(data->philos[thread_nbr].eat, NULL, check_death_or_meals,
			&data->philos[thread_nbr]);
		thread_nbr++;
	}
	thread_nbr = 0;
	while (thread_nbr < data->nb_philo)
	{
		pthread_join(*(data->philos[thread_nbr].t1), NULL);
		pthread_join(*(data->philos[thread_nbr].eat), NULL);
		thread_nbr++;
	}
	if (data->nb_eat != -1)
		pthread_join(*data->meals, NULL);
}

void	free_n_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	exit(1);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	delay(philo->data);
	if (is_even(philo))
		ft_usleep(1);
	while (!(finished(philo->data)))
	{
		eat(philo);
		think(philo);
		phi_sleep(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

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
	init_data(&data, ac, av);
	init_philo(&data);
	init_forks(&data);
	a_table(&data);
	free_n_exit(&data);
	return (0);
}
