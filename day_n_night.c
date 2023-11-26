/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day_n_night.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:13:52 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/26 14:33:42 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	output(t_philo *philo, int status)
{
	if (finished(philo->data))
		return (0);
	pthread_mutex_lock(&philo->data->write);
	if (status == FORK_1 || status == FORK_2)
		printf("%lu %d has taken a fork\n", get_time()
			- philo->data->start_time, philo->id);
	else if (status == EAT)
		printf("%lu %d is eating\n", get_time() - philo->data->start_time,
			philo->id);
	else if (status == SLEEP)
		printf("%lu %d is sleeping\n", get_time() - philo->data->start_time,
			philo->id);
	else if (status == THINK)
		printf("%lu %d is thinking\n", get_time() - philo->data->start_time,
			philo->id);
	else if (status == DIED)
		printf("%lu %d is dead\n", get_time() - philo->data->start_time,
			philo->id);
	else if (status == ALL)
		printf("All philosophers ate %d times\n", philo->data->nb_eat);
	pthread_mutex_unlock(&philo->data->write);
	return (1);
}

int	phi_sleep(t_philo *philo)
{
	if (finished(philo->data))
		return (0);
	pthread_mutex_lock(&philo->lock);
	output(philo, SLEEP);
	ft_usleep(philo->data->tto_sleep);
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

int	think(t_philo *philo)
{
	if (finished(philo->data))
		return (0);
	output(philo, THINK);
	return (1);
}

int	eat(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (finished(philo->data))
		return (0);
	pthread_mutex_lock(&philo->data->forks[philo->fork_l]);
	output(philo, FORK_1);
	pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
	output(philo, FORK_2);
	output(philo, EAT);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->last_eat = get_time();
	ft_usleep(philo->data->tto_eat);
	philo->eat_cont++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
	meal_tracker(philo);
	return (1);
}
