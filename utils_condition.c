/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:34:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/28 14:34:45 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->dead_phi_lock);
	i = data->dead_phi;
	pthread_mutex_unlock(&data->dead_phi_lock);
	return (i);
}

int	must_die(t_philo *philo)
{
	int	should_die;
	uint64_t		time_in_ms;


	should_die = 0;
	time_in_ms = get_time();
	pthread_mutex_lock(&philo->lock);
    // printf("get_time(): %lu\n", time_in_ms);
    // printf("philo->last_eat: %lu\n", philo->last_eat);
    // printf("philo->tto_die: %lu\n", philo->tto_die);
    // printf("\nget_time() - philo->last_eat: \033[1;34m%lu\033[0m\n", (get_time() - philo->last_eat));  // Blue color
	if (get_time() - philo->last_eat > philo->tto_die)
		should_die = 1;
	pthread_mutex_unlock(&philo->lock);
	return (should_die);
}

int	all_ate(t_data *data)
{
	int	all_ate;

	all_ate = 0;
	pthread_mutex_lock(&data->lock);
	if ((data->nb_ate == data->nb_philo) && (data->nb_eat != -1))
	{
		all_ate = 1;
		pthread_mutex_lock(&data->dead_phi_lock);
		data->dead_phi = 1;
		pthread_mutex_unlock(&data->dead_phi_lock);
	}
	pthread_mutex_unlock(&data->lock);
	return (all_ate);
}

int	is_even(t_philo *philo)
{
	int	is_even;

	is_even = 0;
	pthread_mutex_lock(&philo->lock);
	if (philo->id % 2)
		is_even = 1;
	pthread_mutex_unlock(&philo->lock);
	return (is_even);
}
