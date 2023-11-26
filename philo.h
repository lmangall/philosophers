/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:31:55 by lmangall          #+#    #+#             */
/*   Updated: 2023/11/26 13:34:05 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define FORK_1 0
# define FORK_2 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5
# define ALL 6

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				eat_cont;
	int				eating;
	int				fork_l;
	int				fork_r;
	uint64_t		last_eat;
	uint64_t		tto_die;
	pthread_t		*t1;
	pthread_t		*eat;
	pthread_mutex_t	lock;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_eat;
	int				nb_ate;
	int				dead_phi;
	int				thread_nbr;
	int				*threads;
	int				death_thread_id;
	uint64_t		start_time;
	uint64_t		tto_die;
	uint64_t		tto_eat;
	uint64_t		tto_sleep;
	t_philo			*philos;
	pthread_t		*death_thread;
	pthread_t		*meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	dead_phi_lock;
}	t_data;

int			check_args(char **av);
void		*check_meals(void *philo_pointer);
void		a_table(t_data *data);
void		free_n_exit(t_data *data);
void		distrib_forks(t_philo *philo);
void		init_forks(t_data *data);
void		init_philo(t_data *data);
void		init_data(t_data *data, int ac, char **av);
int			eat(void *philo_pointer);
int			phi_sleep(t_philo *philo);
int			think(t_philo *philo);
void		*routine(void *philo_pointer);
int			meal_tracker(t_philo *philo);
void		delay(uint64_t start_time);
int			output(t_philo *philo, int status);
void		*check_death_or_meals(void *philo_pointer);
int			death(t_data *data);
int			ft_atoi(const char *str);
int			finished(t_data *data);
void		ft_usleep(uint64_t time);
uint64_t	get_time(void);
void		*check_all_ate(void *data_pointer);
int			must_die(t_philo *philo);
int			all_ate(t_data *data);
int			is_even(t_philo *philo);

#endif
