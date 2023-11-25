#include "philo.h"

int output(t_philo *philo, int status)
{
	if(philo->data->printed_end == 1)
		return(0);
	if(finish(philo->data))
		return (0);
	pthread_mutex_lock(philo->data->write);
	
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

	pthread_mutex_unlock(philo->data->write);

	return (1);
}

int	phi_sleep(t_philo *philo)
{
	if(finish(philo->data))
		return (0);
	pthread_mutex_lock(&philo->lock);
	output(philo, SLEEP);
	ft_usleep(philo->data->tto_sleep);
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

int	think(t_philo *philo)
{
	if(finish(philo->data))
		return (0);
	output(philo, THINK);
	return (1);

}

//checks if this philo has eaten enough times
int 	meal_tracker(t_philo *philo)
{
	if(philo->eat_cont == philo->data->nb_eat && philo->data->nb_eat != -1 && philo->eat_cont != -1)
	{
		pthread_mutex_lock(philo->data->lock);
		philo->data->nb_ate++;
		pthread_mutex_unlock(philo->data->lock);
		pthread_mutex_lock(&philo->lock);
		philo->eat_cont = -1;
		pthread_mutex_unlock(&philo->lock);
		return(0);
	}
	// if(check_all_ate(philo->data))
	//  	return (0);
	// if (philo->data->nb_ate == philo->data->nb_philo && philo->data->nb_eat != -1)
	// {
	// 	output(philo, ALL);
	// 	pthread_mutex_lock(philo->data->lock);
	// 	philo->data->finished = 1;
	// 	pthread_mutex_unlock(philo->data->lock);
	// 	return (0);
	// }
	return (1);
}

int	eat(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if(finish(philo->data))
		return (0);
	// if(philo->eat_cont == -1)
	// 	return (0);
	pthread_mutex_lock(&philo->data->forks[philo->fork_l]);
	output(philo, FORK_1);
	if(finish(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
			return (0);
		}
	pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
	output(philo, FORK_2);
	output(philo, EAT);
		{
			pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
			pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
			return (0);
		}
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->last_eat = get_time();
	ft_usleep(philo->data->tto_eat);
	philo->eat_cont++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
	if(philo->data->nb_eat != -1)
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
	while (!finish(philo->data))
	{
		if (get_time() - philo->last_eat > philo->data->tto_die)
		{
			pthread_mutex_lock(philo->data->lock);
			output(philo, DIED);
			philo->data->dead_phi = 1;
			pthread_mutex_unlock(philo->data->lock);
			return (NULL);
		}
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;

	pthread_create(philo->eat, NULL, check_death_or_meals, philo);
	delay(philo->data->start_time);
	if (philo->id % 2)
		ft_usleep(1);
	while (!(finish(philo->data)))// && philo->eat_cont != -1)
	{
		eat(philo);
		think(philo);
		phi_sleep(philo);
		
	}
	pthread_join(*(philo->eat), NULL);

	return (NULL);
}
