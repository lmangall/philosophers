
#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

//time_slept is the time since the last eat

// void *eat(void *philo_pointer)
// {
// 	t_philo *philo = (t_philo *)philo_pointer;
// 	t_data *data = philo->data;
// 	int fork_locked = 0;

// // printf("time from start: %llu\n", get_time() - data->start_time);
// // printf("last eat: %llu\n", philo->last_eat);
// // printf("time to sleep: %llu\n", data->tto_sleep);
// // printf("time slept (now-last_eat): %llu\n", (get_time() - data->start_time) - philo->last_eat);

// 	//check if has slept enough
//     if (get_time() - philo->last_eat - data->start_time > philo->data->tto_die)
//     {
// // printf("CONTROL A\n");
//         pthread_mutex_lock(philo->data->lock);
//         philo->data->dead_phi = philo->id; // Update dead_phi
//         pthread_mutex_unlock(philo->data->lock);
//     }
// // printf("CONTROL B\n");
// 	//if time to sleep is less than time slept => execute
// 	if (philo->data->tto_sleep <= ((get_time() - data->start_time) - philo->last_eat))
// 	{	
// // printf("CONTROL C\n");
// 		pthread_mutex_lock(&data->forks[philo->id + 1]);
// 		printf("%llu %d has taken a fork\n", (get_time() - data->start_time), philo->id);
// 		if(philo->id == data->nb_philo)
// 		{
// 			pthread_mutex_lock(&data->forks[0]);//if last philo, takes the first fork
// 			fork_locked = 0;
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(&data->forks[philo->id]);
// 			fork_locked = philo->id;
// 		}
// 		printf("%llu %d has taken a fork\n", (get_time() - data->start_time), philo->id);
// 		philo->status = EATING;

// // printf("CONTROL D\n");
// 		//check if has eaten all meals
// 		if(philo->eat_cont != -1)//-1 means he has eaten all his meals
// 		{
// // printf("CONTROL E\n");
// 			pthread_mutex_lock(&philo->lock);
// 			philo->eat_cont++;
// 			if(philo->eat_cont == data->nb_eat)
// 			{
// 				data->nb_ate++;//add this philo to the number of philos who have eaten all their meals
// 				philo->eat_cont = -1;//this philo has eaten all his meals
// 			}


// 		philo->last_eat = get_time() - data->start_time;
// 		printf("%llu %d is eating\n", (get_time() - data->start_time), philo->id);
// 		//usleep(data->tto_eat * 1000);// time to eat => done in sleep function

// 			pthread_mutex_unlock(&philo->lock);
// 		}



// 		pthread_mutex_unlock(&data->forks[philo->id + 1]);
// 		pthread_mutex_unlock(&data->forks[fork_locked]);
// 	}
// // printf("CONTROL F\n");
// 	//current time is get_time - data->start_time
// 	//time slept is (get_time - data->start_time) - last_eat
// 	return (NULL);
// }


void *eat(void *philo_pointer)
{
	t_philo *philo = (t_philo *)philo_pointer;
	t_data *data = philo->data;
	int fork_locked = 0;

	//
	//check if has eaten all meals
	if(philo->eat_cont != -1)//-1 means he has eaten all his meals
		{
		pthread_mutex_lock(&data->forks[philo->id + 1]);
		pthread_mutex_lock(&philo->write);
		pthread_mutex_unlock(&philo->write);
		printf("%llu %d has taken a fork\n", (get_time() - data->start_time), philo->id);
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
		pthread_mutex_lock(&philo->write);
		printf("%llu %d has taken a fork\n", (get_time() - data->start_time), philo->id);
		pthread_mutex_unlock(&philo->write);
		pthread_mutex_lock(&philo->lock);
		philo->eat_cont++;
		// philo->status = EATING;
		if(philo->eat_cont == data->nb_eat)
		{
			data->nb_ate++;//add this philo to the number of philos who have eaten all their meals
			philo->eat_cont = -1;//this philo has eaten all his meals
		}
		pthread_mutex_lock(&philo->write);
		printf("%llu %d is eating\n", (get_time() - data->start_time), philo->id);
		pthread_mutex_unlock(&philo->write);
		philo->last_eat = get_time() - data->start_time;
		usleep(data->tto_eat * 1000);// time to eat => done in sleep function
		// philo->status = SLEEPING;

			pthread_mutex_unlock(&philo->lock);
		}

		pthread_mutex_unlock(&data->forks[philo->id + 1]);
		pthread_mutex_unlock(&data->forks[fork_locked]);
	
	return (NULL);
}

void	phi_sleep(t_data *data, t_philo *philo)
{		
// printf("control: phi_sleep\n");	
	// philo->status = SLEEPING;
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->write);
	printf("%llu %d is sleeping\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&philo->write);
	usleep(data->tto_sleep * 1000);
	pthread_mutex_unlock(&philo->lock);
}

void	think(t_data *data, t_philo *philo)
{
// printf("control: think\n");
	pthread_mutex_lock(&philo->write);
	// philo->status = THINKING;
	printf("%llu %d is thinking\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&philo->write);

}

void	*check_death_or_meals(void *philo_pointer)
{
// printf("control: check_death_or_meals\n");
	t_philo	*philo = (t_philo *)philo_pointer;
	t_data *data = philo->data;

	while(data->dead_phi == 0)
	{
		pthread_mutex_lock(&philo->lock);


		//check if has slept enough
		if (get_time() - philo->last_eat - data->start_time > philo->data->tto_die)
		{
			pthread_mutex_lock(&philo->write);
			printf("%llu %d died\n", get_time() - philo->data->start_time, philo->id);
			exit (1);//          FINISH   THE    PROGRAM
			pthread_mutex_unlock(&philo->write);
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


		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void *routine(void *philo_pointer)
{
// printf("control: routine\n");
	t_philo	*philo = (t_philo *)philo_pointer;

//	pthread_create(&philo->t1, NULL, check_death, philo);

	while(philo->data->dead_phi == 0)
	{
		//is it necessary to have eat as a pthread ?
	pthread_create(&philo->eat, NULL, check_death_or_meals, philo);
	while(philo->data->dead_phi == 0)
		eat(philo);
	pthread_join(philo->eat, NULL);
		phi_sleep(philo->data, philo);
		//eat(philo->data, philo);
		think(philo->data, philo);
	}
//	pthread_join(philo->t1, NULL);

	return (NULL);
}
