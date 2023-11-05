#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void *eat(void *philo_pointer)
{
	t_philo *philo = (t_philo *)philo_pointer;
	t_data *data = philo->data;
	int fork_locked = 0;


	//check if has eaten all meals
	if(philo->eat_cont != -1)//-1 means he has eaten all his meals
		{
		pthread_mutex_lock(&data->forks[philo->id + 1]);
		pthread_mutex_lock(data->write);
		printf("%llu %d has taken a fork\n", (get_time() - data->start_time), philo->id);
		pthread_mutex_unlock(data->write);
		if(philo->id == data->nb_philo)
		{
			pthread_mutex_lock(&data->forks[0]);//if last philo, takes the first fork
			fork_locked = 0;
		}
		else
		{
			pthread_mutex_lock(&data->forks[philo->id]);
			fork_locked = philo->id;
		}
		pthread_mutex_lock(data->write);
		printf("%llu %d has taken a fork\n", (get_time() - data->start_time), philo->id);
		pthread_mutex_unlock(data->write);
		pthread_mutex_lock(&philo->lock);
		philo->eat_cont++;
		// philo->status = EATING;
		if(philo->eat_cont == data->nb_eat)
		{
			data->nb_ate++;//add this philo to the number of philos who have eaten all their meals
			philo->eat_cont = -1;//this philo has eaten all his meals
		}
		pthread_mutex_lock(data->write);
		printf("%llu %d is eating\n", (get_time() - data->start_time), philo->id);
		pthread_mutex_unlock(data->write);
		
		philo->last_eat = get_time();//last time ate

		usleep(data->tto_eat * 1000);// time to eat => done in sleep function
			pthread_mutex_unlock(&philo->lock);
		}

		pthread_mutex_unlock(&data->forks[philo->id + 1]);
		pthread_mutex_unlock(&data->forks[fork_locked]);
	
	return (NULL);
}

void	phi_sleep(t_data *data, t_philo *philo)
{		
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(data->write);
	printf("%llu %d is sleeping\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(data->write);
	usleep(data->tto_sleep * 1000);
	pthread_mutex_unlock(&philo->lock);
}

void	think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(data->write);
	printf("%llu %d is thinking\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(data->write);

}

void	*check_death_or_meals(void *philo_pointer)
{
	t_philo	*philo = (t_philo *)philo_pointer;
	t_data *data = philo->data;

	while(data->dead_phi == 0)
	{
		pthread_mutex_lock(&philo->lock);
	
		//check if has slept enough
		if (get_time() - philo->last_eat > philo->data->tto_die)
		{
			pthread_mutex_lock(data->write);
			printf("%llu %d died\n", get_time() - philo->data->start_time, philo->id);
			exit (1);//          FINISH   THE    PROGRAM
			pthread_mutex_unlock(data->write);
			// pthread_mutex_lock(philo->data->lock);
			// philo->data->dead_phi = philo->id; // Update dead_phi
			// pthread_mutex_unlock(philo->data->lock);
		}

		//check if has eaten all meals
		if(philo->eat_cont != -1)//-1 means he has eaten all his meals
		{
			if(philo->eat_cont == data->nb_eat)
			{
				pthread_mutex_lock(data->lock);
				data->nb_ate++;//add this philo to the number of philos who have eaten all their meals
				pthread_mutex_unlock(data->lock);
				philo->eat_cont = -1;//this philo has eaten all his meals
			}
		}

		//check if any philo has eaten all his meals   => is this necessary ?
		if(data->nb_ate == data->nb_philo)
		{
			pthread_mutex_lock(data->write);
			printf("All philosophers ate %d times\n", data->nb_eat);
			pthread_mutex_unlock(data->write);
			exit (1);//          FINISH   THE    PROGRAM
		}


		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void *routine(void *philo_pointer)
{
	t_philo	*philo = (t_philo *)philo_pointer;

	while(philo->data->dead_phi == 0)
	{
	pthread_create(&philo->eat, NULL, check_death_or_meals, philo);
	while(philo->data->dead_phi == 0)
		eat(philo);
	pthread_join(philo->eat, NULL);
		phi_sleep(philo->data, philo);
		think(philo->data, philo);
	}
	return (NULL);
}
