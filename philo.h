
#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>


typedef struct s_philo 
{
	struct s_data	*data; 		/**< Pointer to the simulation data. */
	pthread_t		t1;			 /**< Philosopher's thread. */
	int				id;			/**< Philosopher's unique identifier. */
	int				eat_cont; 	/**< Number of times the philosopher has eaten. */
	int				status; 	/**< Current status of the philosopher (alive or dead). */
	int				eating; 	/**< Flag indicating if the philosopher is currently eating. */
	uint64_t		time_to_die;/**< Time in milliseconds before a philosopher dies if they haven't eaten. */
	pthread_mutex_t	lock;		/**< Mutex lock for this philosopher's state. */
	pthread_mutex_t	*r_fork; 	/**< Mutex lock for the right fork. */
	pthread_mutex_t	*l_fork; 	/**< Mutex lock for the left fork. */
} t_philo;


typedef struct s_data 
{
    pthread_t		*tid;		/**< Array of philosopher threads. */
    int				nb_philo;	/**< Number of philosophers in the simulation. */
    int				tto_die;	/**< Time in milliseconds before a philosopher dies if they haven't eaten. */
    int				tto_eat;	/**< Time in milliseconds required for a philosopher to eat. */
    int				tto_sleep;	/**< Time in milliseconds required for a philosopher to sleep. */
    int				nb_eat;		/**< Number of times each philosopher must eat (optional). */
    t_philo			*philos;	/**< Array of philosophers. */
    uint64_t		death_time;	/**< Time in milliseconds when a philosopher will die if they haven't eaten. */
    uint64_t		eat_time;	/**< Time in milliseconds required for a philosopher to eat. */
    uint64_t		sleep_time;	/**< Time in milliseconds required for a philosopher to sleep. */
    uint64_t		start_time;	/**< Time when the simulation started. */
    pthread_mutex_t	*forks;		/**< Array of mutex locks for the forks. */
    pthread_mutex_t	lock;		/**< Mutex lock for controlling access to shared data. */
    pthread_mutex_t	write;		/**< Mutex lock for writing output. */
} t_data;

/**
 * @brief Check the validity of command line arguments for the dining philosophers program.
 *
 * This function validates the command line arguments provided to the dining philosophers program.
 *
 * @param av An array of command line arguments.
 * @param arg1 Number of philosophers and number of forks.
 * @param arg2 Time in ms before a philosopher dies if they haven't eaten.
 * @param arg3 Time in ms required for a philosopher to eat with two forks.
 * @param arg4 Time in ms required for a philosopher to sleep.
 * @param arg5 Number of times each philosopher must eat (optional).
 *
 * @return 1 if all arguments are valid, 0 if any argument is invalid.
 */
int check_args(char **av);

/**
* @brief converts the string argument str to an integer (type int).
* @param str − This is the string representation of an integral number.
* @return This function returns the converted integral number as an int
* value. If no valid conversion could be performed, it returns zero.
*/
int			ft_atoi(const char *str);



#endif