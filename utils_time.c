/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:40:46 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/28 14:29:54 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(uint64_t time)
{
	uint64_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
	{
		usleep(10);
	}
}


uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}






// time_t	get_time_in_ms(void)
// {
// 	struct timeval		tv;

// 	gettimeofday(&tv, NULL);
// 	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// }


// long long	current_timestamp(struct timeval start_time)
// {
// 	struct timeval	now;
// 	long long		elapsed_time;

// 	gettimeofday(&now, NULL);
// 	elapsed_time = (now.tv_sec - start_time.tv_sec) * 1000;
// 	elapsed_time += (now.tv_usec - start_time.tv_usec) / 1000;
// 	return (elapsed_time);
// }

// void	delay(t_data *data)
// {
// 	int	time;
	
// 	pthread_mutex_lock(&data->lock);
// 	time = data->start_time;
// 	pthread_mutex_unlock(&data->lock);
// 	while (get_time() < time)
// 		continue ;
// }
