
#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void	eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->forks[philo->id]);
	pthread_mutex_lock(&data->forks[philo->id + 1]);
	philo->status = EATING;
	philo->eat_cont++;
	printf("%llu %d is eating\n", (get_time() - data->start_time), philo->id);
	usleep(data->tto_eat * 1000);// Since there are 1000 microseconds in a millisecond, you can multiply tto_eat by 1000 to achieve the desired delay in microseconds.
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[philo->id + 1]);
}

void	phi_sleep(t_data *data, t_philo *philo)
{
	philo->status = SLEEPING;
	printf("%llu %d is sleeping\n", get_time() - data->start_time, philo->id);
	usleep(data->tto_sleep * 1000);
}

void	think(t_data *data, t_philo *philo)
{
	philo->status = THINKING;
	printf("%llu %d is thinking\n", get_time() - data->start_time, philo->id);
}

void *routine(void *arg)
{
printf("control: routine\n");
	t_philo	*philo = (t_philo *)arg;
	//check_death(data, philo);
	// int i = 0;
	// while (i < 10)
	// {
		eat(philo->data, philo);
		phi_sleep(philo->data, philo);
		think(philo->data, philo);
// i++;
// 	}
	return (NULL);
}