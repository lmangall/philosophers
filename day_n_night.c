#include "philo.h"

int output(t_philo *philo, int status)
{
	if(finished(philo->data))
		return (0);
	pthread_mutex_lock(&philo->data->write);
	
	if (status == FORK_1 || status == FORK_2)
		printf("%lu %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
	else if (status == EAT)
		printf("%lu %d is eating\n", get_time() - philo->data->start_time, philo->id);
	else if (status == SLEEP)
		printf("%lu %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
	else if (status == THINK)
		printf("%lu %d is thinking\n", get_time() - philo->data->start_time, philo->id);
	else if (status == DIED)
	{
		printf("\033[91m%lu %d is dead\033[0m\n", get_time() - philo->data->start_time, philo->id);
		    // pthread_mutex_lock(philo->data->lock);
			// philo->data->printed_end = 1;
		    // pthread_mutex_unlock(philo->data->lock);
	}
	else if (status == ALL)
	{
		printf("\033[31mAll philosophers ate %d times\033[0m\n", philo->data->nb_eat);
		    // pthread_mutex_lock(philo->data->lock);
			// philo->data->printed_end = 1;
		    // pthread_mutex_unlock(philo->data->lock);
	}

	pthread_mutex_unlock(&philo->data->write);

	return (1);
}

int	phi_sleep(t_philo *philo)
{
	if(finished(philo->data))
		return (0);
	pthread_mutex_lock(&philo->lock);
	output(philo, SLEEP);
	ft_usleep(philo->data->tto_sleep);
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

int	think(t_philo *philo)
{
	
	if(finished(philo->data))
		return (0);
	output(philo, THINK);
	return (1);

}

//check if this philo has eaten all his meals
int meal_tracker(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->lock);
    pthread_mutex_lock(&philo->lock);

    if (philo->eat_cont == philo->data->nb_eat && philo->data->nb_eat != -1 && philo->eat_cont != -1)
    {
        philo->data->nb_ate++;
        philo->eat_cont = -1;
		// pthread_mutex_lock(&philo->data->dead_phi_lock);
		// philo->data->dead_phi = 1;
		// pthread_mutex_unlock(&philo->data->dead_phi_lock);
        pthread_mutex_unlock(&philo->lock);
        pthread_mutex_unlock(&philo->data->lock);
        
        return 1;
    }

    pthread_mutex_unlock(&philo->lock);
    pthread_mutex_unlock(&philo->data->lock);

    return 0;
}


int	eat(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if(finished(philo->data))
		return (0);

	// if(philo->eat_cont == -1)
	// 	return (0);
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

//checks if any philo is dead
void *check_death_or_meals(void *philo_pointer) 
{
	t_philo *philo = (t_philo *)philo_pointer;
	int i;

	i = 0;
	delay(philo->data->start_time);
	while (!(finished(philo->data)))
	{
		// if (get_time() - philo->last_eat > philo->data->tto_die)
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

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;

	// pthread_detach(*(philo->eat));  // Detach the thread
	delay(philo->data->start_time);
	if (is_even(philo))
		ft_usleep(1);
	while (!(finished(philo->data)))
	{
		eat(philo);
		think(philo);
		phi_sleep(philo);
		
	}

	return (NULL);
}
