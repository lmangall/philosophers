/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:13:57 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/26 14:17:28 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	mult;

	nb = 0;
	i = 0;
	mult = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mult = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (mult * nb);
}

void	*check_all_ate(void *data_pointer)
{
	t_data	*data;

	data = (t_data *)data_pointer;
	delay(data);
	while (!(finished(data)))
	{
		if (all_ate(data))
		{
			pthread_mutex_lock(&data->write);
			printf("All philosophers ate %d times\n", data->nb_eat);
			pthread_mutex_unlock(&data->write);
			return (NULL);
		}
	}
	return (NULL);
}

int	meal_tracker(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_lock(&philo->lock);
	if (philo->eat_cont == philo->data->nb_eat && philo->data->nb_eat != -1
		&& philo->eat_cont != -1)
	{
		philo->data->nb_ate++;
		philo->eat_cont = -1;
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

void	*check_death_or_meals(void *philo_pointer)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_pointer;
	i = 0;
	delay(philo->data);
	while (!(finished(philo->data)))
	{
		if (must_die(philo))
		{
			output(philo, DIED);
			pthread_mutex_lock(&philo->data->dead_phi_lock);
			philo->data->dead_phi = 1;
			pthread_mutex_unlock(&philo->data->dead_phi_lock);
			return (NULL);
		}
	}
	return (NULL);
}
