/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day_n_night.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:13:52 by lmangall          #+#    #+#             */
/*   Updated: 2023/12/07 12:43:35 by lmangall         ###   ########.fr       */
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
		if (!(finished(philo->data)))
			printf("%lu %d died\n",
				get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	return (1);
}

int	phi_sleep(t_philo *philo)
{
	if (finished(philo->data))
		return (0);
	output(philo, SLEEP);
	usleep(philo->data->tto_sleep * 1000);
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
	pthread_mutex_lock(&philo->food_lock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->food_lock);
	usleep(philo->tto_eat * 1000);
	// pthread_mutex_lock(&philo->eat_cont_lock);
	philo->eat_cont++;
	// if (is_even(philo))
	// 	usleep(1);
	// pthread_mutex_unlock(&philo->eat_cont_lock);
	// if (is_even(philo))
	//  	usleep(1);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
	meal_tracker(philo);
	return (1);
}

static int starve(t_philo *philo)
{
	int starve_time;
	uint64_t time_since_last_eat;

	pthread_mutex_lock(&philo->food_lock);
	time_since_last_eat = get_time() - philo->last_eat;
	pthread_mutex_unlock(&philo->food_lock);

	if (time_since_last_eat < (uint64_t)philo->data->tto_die)
	{
		starve_time = philo->data->tto_die - time_since_last_eat;
		starve_time = 0.85 * starve_time;
		usleep(starve_time * 1000);
		// printf("   starving\n");
	}

	return 1;
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;


	philo = (t_philo *)philo_pointer;

	pthread_mutex_lock(&philo->food_lock);
	if (philo->last_eat == (uint64_t)-1)
		philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->food_lock);
	if (!(is_even(philo)))
		usleep(1);
	while (!(finished(philo->data)))
	{
		eat(philo);
		// usleep(100);
		phi_sleep(philo);
		think(philo);
		// if (is_even(philo))
			starve(philo);
	}
	return (NULL);
}
