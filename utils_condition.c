/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:34:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/26 14:34:46 by lmangall         ###   ########.fr       */
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

	should_die = 0;
	pthread_mutex_lock(&philo->lock);
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
