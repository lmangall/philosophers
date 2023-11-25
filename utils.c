#include "philo.h"

int	ft_atoi(const char *str)
{
	int nb;
	int i;
	int mult;

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

void	ft_usleep(uint64_t time)
{
	uint64_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
	{
		usleep(10);//or 		continue ;
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

void	delay(uint64_t start_time)
{
	while (get_time() < start_time)
		continue ;
}


void	*check_all_ate(void *data_pointer)
{
	t_data *data = (t_data *)data_pointer;
	while (!(data->dead_phi))
	{
		if ((data->nb_ate == data->nb_philo) && (data->nb_eat != -1))
		{
			pthread_mutex_lock(&data->lock);
			data->dead_phi = 1;
			pthread_mutex_unlock(&data->lock);
			pthread_mutex_lock(&data->write);
			printf("\033[31mAll philosophers ate %d times\033[0m\n", data->nb_eat);
			pthread_mutex_unlock(&data->write);
			return (NULL);
		}
	}
	return (NULL);
}
