/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:34:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/12/07 13:31:24 by lmangall         ###   ########.fr       */
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
	int				should_die;

	should_die = 0;
	pthread_mutex_lock(&philo->food_lock);
	if (get_time() - philo->last_eat > philo->data->tto_die)
		should_die = 1;
	pthread_mutex_unlock(&philo->food_lock);
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
	if (philo->id % 2)
		is_even = 1;
	return (is_even);
}

/**
 * @brief Manages the acquisition or release of forks for a philosopher.
 * If the number of philosophers is odd,
 * it follows a specific order for locking and unlocking to prevent deadlock.
 */
int	manage_forks(t_philo *philo, int lock)
{
	if (philo->data->nb_philo % 2 && !(lock))
	{
		pthread_mutex_lock(&philo->data->forks[philo->fork_l]);
		output(philo, FORK_1);
		pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
		output(philo, FORK_2);
	}
	if (philo->data->nb_philo % 2 && lock)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
		pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
	}
	if (!(philo->data->nb_philo % 2) && !(lock))
	{
		pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
		output(philo, FORK_2);
		pthread_mutex_lock(&philo->data->forks[philo->fork_l]);
		output(philo, FORK_1);
	}
	if (!(philo->data->nb_philo % 2) && lock)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
		pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
	}
	return (1);
}
