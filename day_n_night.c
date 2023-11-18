#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void	*eat(void *philo_pointer)
{
	t_philo	*philo;
	int		first_fork;
	int		second_fork;

	philo = (t_philo *)philo_pointer;
// printf("inside eat for philo %d\n", philo->id);
	if (philo->eat_cont == -1 || philo->data->dead_phi == 1)
		{
		printf("returned eat for philo %d\n", philo->id);
		return (NULL);
		}
	// printf("after return eat for philo %d\n", philo->id);

	while (philo->data->dead_phi == 0)
	{
		first_fork = philo->id;
		second_fork = (philo->id + 1); //% philo->data->nb_philo;//check if correct given ther is no philo 0
		if (first_fork == philo->data->nb_philo)
			second_fork = 1;
	// printf("in while in eat for philo %d\n", philo->id);
		pthread_mutex_lock(&philo->data->forks[first_fork - 1]);
		pthread_mutex_lock(&philo->data->forks[second_fork - 1]);
				if (philo->data->dead_phi == 1)
					{
					printf("BAAACK%d\n", philo->id);
							pthread_mutex_unlock(&philo->data->forks[first_fork - 1]);
					pthread_mutex_unlock(&philo->data->forks[second_fork - 1]);
					return (NULL);
					}
		pthread_mutex_lock(philo->data->write);
		printf("%lu %d has taken a fork\n", get_time()
			- philo->data->start_time, philo->id);
		printf("%lu %d has taken a fork\n", get_time()
			- philo->data->start_time, philo->id);
		printf("%lu %d is eating\n", get_time() - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(philo->data->write);
		pthread_mutex_lock(&philo->lock);
		philo->eating = 1;
		usleep(philo->data->tto_eat * 1000); // this is done before: first eat, then write time last eate
		philo->last_eat = get_time();
		philo->eat_cont++;
		philo->eating = 0;
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->data->forks[first_fork - 1]);
		pthread_mutex_unlock(&philo->data->forks[second_fork - 1]);
// printf("end of eat for philo %d\n", philo->id);
	}
	return (NULL);
}

void	phi_sleep(t_data *data, t_philo *philo)
{
	if (philo->data->dead_phi == 0)
		{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(data->write);
		printf("%lu %d is sleeping\n", get_time() - data->start_time, philo->id);
		pthread_mutex_unlock(data->write);
		usleep(data->tto_sleep * 1000);
		pthread_mutex_unlock(&philo->lock);
		}
}

void	think(t_data *data, t_philo *philo)
{
	if (philo->data->dead_phi == 1)
		{
		pthread_mutex_lock(data->write);
		printf("%lu %d is thinking\n", get_time() - data->start_time, philo->id);
		pthread_mutex_unlock(data->write);
		}
}

void *check_death_or_meals(void *philo_pointer) {
    t_philo *philo = (t_philo *)philo_pointer;
    t_data *data = philo->data;
// printf("from check death: philo->data->dead_phi == %d\n", philo->data->dead_phi);
    while (data->dead_phi == 0 && philo->eat_cont != -1) {
        pthread_mutex_lock(&philo->lock);

		if (get_time() - philo->last_eat > philo->data->tto_die)
		{
            pthread_mutex_lock(data->write);
            printf("%lu %d died\n", get_time() - philo->data->start_time, philo->id);
            pthread_mutex_unlock(data->write);

            pthread_mutex_lock(data->lock);
            data->dead_phi = 1;
// printf("XXXdata->dead_phi == %d\n", data->dead_phi);

            pthread_mutex_unlock(data->lock);

            pthread_mutex_unlock(&philo->lock);
            return (NULL);
        }
        if (philo->eat_cont > 0) 
		{
            if ((philo->eat_cont >= data->nb_eat) && (data->nb_eat != -1)) {
                pthread_mutex_lock(data->lock);
                data->nb_ate++;
                pthread_mutex_unlock(data->lock);

                if (data->nb_ate == data->nb_philo) {
                    pthread_mutex_lock(data->write);
                    printf("All philosophers ate %d times\n", data->nb_eat);
                    pthread_mutex_unlock(data->write);
                    exit(1);
                }
                philo->eat_cont = -1;
            }
        }
        if (data->nb_ate == data->nb_philo) 
		{
            pthread_mutex_lock(data->write);
            printf("All philosophers ate %d times\n", data->nb_eat);
            pthread_mutex_unlock(data->write);
            exit(1);
        }
        pthread_mutex_unlock(&philo->lock);
        usleep(1000);
    }

    return (NULL);
}


void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	pthread_create(&philo->eat, NULL, check_death_or_meals, philo);
    //pthread_detach(philo->eat);
        if (philo->data->dead_phi == 1)
		{
				pthread_join(philo->eat, NULL);
				return (NULL);
		}
// printf("philo->data->dead_phi == %d\n", philo->data->dead_phi);
	while (philo->eat_cont != -1 && philo->data->dead_phi == 0)
	{
		eat(philo);
        if (philo->data->dead_phi == 1)
		{
				pthread_join(philo->eat, NULL);
				return (NULL);
		}
		phi_sleep(philo->data, philo);
		think(philo->data, philo);
// printf("routine loop\n");
	}
// printf("routine \n");
	pthread_join(philo->eat, NULL);
// printf("joined? \n");

	return (NULL);
}




