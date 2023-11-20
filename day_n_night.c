#include "philo.h"
#define FORK_1  0
#define FORK_2  1
#define EAT  2
#define SLEEP 3
#define THINK 4
#define DIED 5

// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;

// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(time / 10);
// 	return (0);
// }

void output(t_philo *philo, int status)
{
    pthread_mutex_lock(philo->data->write);

    // if (has_simulation_stopped(philo->table) == true && reaper_report == false)
    // {
    //     pthread_mutex_unlock(&philo->table->write_lock);
    //     return;
    // }

    if (status == FORK_1 || status == FORK_2)
        printf("%llu %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
    else if (status == EAT)
        printf("%llu %d is eating\n", get_time() - philo->data->start_time, philo->id);
    else if (status == SLEEP)
        printf("%llu %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
    else if (status == THINK)
        printf("%llu %d is thinking\n", get_time() - philo->data->start_time, philo->id);
    else if (status == DIED)
        printf("%llu %d is dead\n", get_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(philo->data->write);
}

void	phi_sleep(t_philo *philo)
{
	if (philo->data->dead_phi == 0)
	{
		pthread_mutex_lock(&philo->lock);
		output(philo, SLEEP);
		ft_usleep(philo->data->tto_sleep);
		pthread_mutex_unlock(&philo->lock);
	}
}

void	think(t_philo *philo)
{
	output(philo, THINK);
}

// void	philo_sleep(uint64_t sleep_time)
// {
// 	uint64_t	wake_up;

// 	wake_up = get_time() + sleep_time;
// 	while (get_time() < wake_up)
// 	{
// 		usleep(100);
// 	}
// }

void	delay(uint64_t start_time)
{
	while (get_time() < start_time)
		continue ;
}

void	*eat(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
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
// printf("end of eat for philo %d\n", philo->id);
	return (NULL);
}



int death(t_data *data)
{
	int i;

	i = 0;
	while(i++ < data->nb_philo)
	{
		if (get_time() - data->philos[i].last_eat > data->tto_die)
		{
			printf("   dead\n");
            pthread_mutex_lock(data->lock);
            pthread_mutex_lock(&data->philos[i].lock);
            output(&data->philos[i], DIED);
            data->dead_phi = 1;
			pthread_mutex_unlock(data->lock);
			pthread_mutex_unlock(&data->philos[i].lock);
            return (1);
        }
		
	}
		return(0);
}

void *check_death_or_meals(void *data_pointer) 
{
    t_data *data = (t_data *)data_pointer;

	delay(data->start_time);
	while (true)
	{
		if (death(data) == 1)
			return (NULL);
		usleep(1000);
	}
    return (NULL);
}



void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;

    // pthread_mutex_lock(&philo->lock);
	// pthread_mutex_unlock(&philo->lock);

	delay(philo->data->start_time);
	if (philo->id % 2)
		ft_usleep(1);
	while (dead(philo->data) == 0)
	{
		eat(philo);
		think(philo);
		phi_sleep(philo);
	}

	return (NULL);
}




