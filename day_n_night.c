#include "philo.h"
#define FORK_1  0
#define FORK_2  1
#define EAT  	2
#define SLEEP 	3
#define THINK 	4
#define DIED 	5
#define ALL 	6

int output(t_philo *philo, int status)
{
	// if((philo->data->finished == 1 || philo->data->dead_phi == 1))
	//  	free_n_exit(philo->data);
	// if(philo->data->dead_phi == 1)// || (philo->data->nb_ate >= philo->data->nb_philo && philo->data->nb_eat != -1))
	// 	return (0);
	pthread_mutex_lock(philo->data->write);
	// if (has_simulation_stopped(philo->table) == true && reaper_report == false)
	// {
	//     pthread_mutex_unlock(&philo->table->write_lock);
	//     return;
	// }


	if ((status == FORK_1 || status == FORK_2) && (philo->data->finished == 0 && philo->data->dead_phi == 0))
		printf("%llu %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
	else if ((status == EAT) && (philo->data->finished == 0 && philo->data->dead_phi == 0))
		printf("%llu %d is eating\n", get_time() - philo->data->start_time, philo->id);
	else if ((status == SLEEP) && (philo->data->finished == 0 && philo->data->dead_phi == 0))
		printf("%llu %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
	else if ((status == THINK) && (philo->data->finished == 0 && philo->data->dead_phi == 0))
		printf("%llu %d is thinking\n", get_time() - philo->data->start_time, philo->id);
	else if (((status == DIED) || (philo->data->finished == 1 || philo->data->dead_phi == 1)) && philo->data->printed_end == 0)
	{
		printf("%llu %d is dead\n", get_time() - philo->data->start_time, philo->id);
			philo->data->printed_end = 1;
		 	free_n_exit(philo->data);
			// return (0);
	}
	else if ((status == ALL) && (philo->data->finished == 0 || philo->data->dead_phi == 0) && philo->data->printed_end == 0)
	{
		printf("All philosophers ate %d times\n", philo->data->nb_eat);
			philo->data->printed_end = 1;
		 	free_n_exit(philo->data);
			// return (0);
	}
	else
	{
		free_n_exit(philo->data);
		return (0);
	}
	pthread_mutex_unlock(philo->data->write);

	return (1);
}

void	phi_sleep(t_philo *philo)
{
	if((philo->data->finished == 1 || philo->data->dead_phi == 1))
	 	free_n_exit(philo->data);
	pthread_mutex_lock(&philo->lock);
	output(philo, SLEEP);
	ft_usleep(philo->data->tto_sleep);
	pthread_mutex_unlock(&philo->lock);
}

void	think(t_philo *philo)
{
	if((philo->data->finished == 1 || philo->data->dead_phi == 1))
	 	free_n_exit(philo->data);
	output(philo, THINK);
}

int 	meal_tracker(t_philo *philo)
{
	// if(philo->eat_cont == -1)
	// 	return (1);
	if(philo->eat_cont == philo->data->nb_eat && philo->data->nb_eat != -1)
	{
		pthread_mutex_lock(philo->data->lock);
		philo->data->nb_ate++;
		pthread_mutex_unlock(philo->data->lock);
		pthread_mutex_lock(&philo->lock);
		philo->eat_cont = -1;
		pthread_mutex_unlock(&philo->lock);
	}
	if (philo->data->nb_ate == philo->data->nb_philo && philo->data->nb_eat != -1)
	{
		output(philo, ALL);
		philo->data->finished = 1;
		free_n_exit(philo->data);
		// pthread_mutex_lock(philo->data->lock);
		// philo->data->dead_phi = 1;
		// pthread_mutex_unlock(philo->data->lock);
		return (0);
	}
	return (1);
}

int	check_all_ate(t_data *data)
{
printf("\n\n      control");
	if (data->nb_ate == data->nb_philo)
	{
		output(&data->philos[0], ALL);
		data->dead_phi = 1;
		return (1);
	}
	return (0);
}

void	*eat(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if(philo->data->dead_phi == 1 || philo->data->finished == 1)
		return (NULL);
	pthread_mutex_lock(&philo->data->forks[philo->fork_l]);
	if (!output(philo, FORK_1))
		return (NULL);
	pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
	if (!output(philo, FORK_2))
		return (NULL);	
	if (!output(philo, EAT))
		return (NULL);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->last_eat = get_time();
	ft_usleep(philo->data->tto_eat);
	philo->eat_cont++;
	// philo->data->nb_ate++;
	// if(philo->eat_cont == philo->data->nb_eat && philo->data->nb_eat != -1)
	// {
	// 	printf("\n\n      philo->eat_cont: %d\n", philo->eat_cont);
	// 	printf("      philo->data->nb_ate: %d\n\n\n", philo->data->nb_ate);
	// 	philo->data->nb_ate++;
	// 	if (check_all_ate(philo->data))
	// 		return (NULL);
	// }
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	if (!meal_tracker(philo))
		return (NULL);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
	return (NULL);
}

void *check_death_or_meals(void *data_pointer) 
{
    t_data *data = (t_data *)data_pointer;
	int i;
		printf("\n\n       nb_philo: %d\n", data->nb_philo);

	i = 0;
	delay(data->start_time);

	// while (data->dead_phi == 0)
	// {
	// 	if (data->nb_ate == data->nb_philo)
	// 	{
	// 		output(&data->philos[i], ALL);
	// 		return (NULL);
	// 	}
	// 	(void)data;
	// }
    while (1)
    {
        while (i < data->nb_philo)
        {
            if (get_time() - data->philos[i].last_eat > data->tto_die)
            {
                pthread_mutex_lock(data->lock);
                output(&data->philos[i], DIED);
                data->dead_phi = 1;
				// pthread_mutex_lock(data->write);
                pthread_mutex_unlock(data->lock);
                return (NULL);
            }
            i++;
			// if(check_all_ate(data))
			// 	return (NULL);
        }
		if(meal_tracker(&data->philos[0]) == 0)
			return (NULL);	
        i = 0;  // Reset i to 0 after the inner while loop
    }
    return (NULL);
}


void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;

	delay(philo->data->start_time);
	if (philo->id % 2)
		ft_usleep(1);
	while (finish(philo->data) == 0)
	{
		if(philo->eat_cont == -1)
			break;
		eat(philo);
		if((philo->data->finished == 1 || philo->data->dead_phi == 1))
		 	free_n_exit(philo->data);
		think(philo);
		phi_sleep(philo);
	}
	free_n_exit(philo->data);

	return (NULL);
}




