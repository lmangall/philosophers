
#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>

#define EATING 1
#define SLEEPING 2
#define THINKING 3
#define DEAD 4

// number_of_philosophers time_to_die time_to_eat time_to_sleep
//[number_of_times_each_philosopher_must_eat]

typedef struct s_philo 
{
	struct s_data	*data;      /**< Pointer to the data struct. */
	pthread_t		t1;			/**< Philosopher's thread. */
    pthread_t       eat;        /**< Philosopher's thread. */
	int				id;			/**< Philosopher's unique identifier. */
	int				eat_cont; 	/**< Number of times the philosopher has eaten. */
	int				status; 	/**< Current status of the philosopher (alive or dead). */
	int				eating; 	/**< Flag indicating if the philosopher is currently eating. */
	int             dead_or_alive; /**< Flag indicating if the philosopher is currently dead or alive. */
    uint64_t        last_eat;	/**< Time in milliseconds when the philosopher last ate. */
    uint64_t		time_to_die;/**< Time in milliseconds before a philosopher dies if they haven't eaten. */
	pthread_mutex_t	lock;		/**< Mutex lock for this philosopher's state. */
	pthread_mutex_t	*r_fork; 	/**< Mutex lock for the right fork. */
	pthread_mutex_t	*l_fork; 	/**< Mutex lock for the left fork. */
} t_philo;


typedef struct s_data 
{
    pthread_t		*tid;		/**< Array of philosopher threads. */
    int				nb_philo;	/**< Number of philosophers in the simulation. */
    uint64_t		tto_die;	/**< Time in milliseconds before a philosopher dies if they haven't eaten. */
    uint64_t		tto_eat;	/**< Time in milliseconds required for a philosopher to eat. */
    uint64_t		tto_sleep;	/**< Time in milliseconds required for a philosopher to sleep. */
    int				nb_eat;		/**< Number of times each philosopher must eat (optional). */
    int             nb_ate;     /**< Number of times each philosopher has eaten all his meals */
    int             dead_phi;   /**< Number of philosophers that are dead */
    t_philo			*philos;	/**< Array of philosophers. */
    uint64_t		start_time;	/**< Time when the simulation started. */
    pthread_mutex_t	*forks;		/**< Array of mutex locks for the forks. */
    pthread_mutex_t	*lock;		/**< Mutex lock for controlling access to shared data. */
} t_data;
//is data->forks necessary ?

//                                in main.c :
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

void    *check_death(void *philo_pointer);
void    a_table(t_data *data);

//                                in init.c :

void	init_forks(t_data *data);

/**
 * Initialize the philosophers with the given data.
 *
 * @param data The data structure containing configuration.
 */
void init_philo(t_data *data);

/**
 * Initialize the data structure with command-line arguments.
 *
 * @param data The data structure to initialize.
 * @param ac   The number of command-line arguments.
 * @param av   An array of command-line argument strings.
 */
void init_data(t_data *data, int ac, char **av);

/**
 * Initialize mutexes.
 *
 * @param data The data structure containing configuration.
 */
//void init_mutex(t_data *data);



//                                in days_n_night
/**
 * Get the current time in milliseconds.
 *
 * @return The current time in milliseconds.
 */
uint64_t get_time(void);
/**
 * Simulate a philosopher eating.
 *
 * @param philo The philosopher's data.
 */
void *eat(void *philo_pointer);

/**
 * Simulate a philosopher sleeping.
 *
 * @param data  The data structure containing configuration.
 * @param philo The philosopher's data.
 */
void phi_sleep(t_data *data, t_philo *philo);

/**
 * Simulate a philosopher thinking.
 *
 * @param data  The data structure containing configuration.
 * @param philo The philosopher's data.
 */
void think(t_data *data, t_philo *philo);

/**
 * The main routine for a philosopher's behavior.
 *
 * @param arg The philosopher's data.
 * @return NULL.
 */
void *routine(void *arg);


//                                in utils.c :

/**
* @brief converts the string argument str to an integer (type int).
* @param str − This is the string representation of an integral number.
* @return This function returns the converted integral number as an int
* value. If no valid conversion could be performed, it returns zero.
*/
int			ft_atoi(const char *str);

/**
 * Initialize the philosophers with the given data.
 *
 * @param data The data structure containing configuration.
 */
void init_philo(t_data *data);

/**
 * Initialize mutexes.
 *
 * @param data The data structure containing configuration.
 */
void init_mutex(t_data *data);

/**
 * Initialize the data structure with command-line arguments.
 *
 * @param data The data structure to initialize.
 * @param ac   The number of command-line arguments.
 * @param av   An array of command-line argument strings.
 */
void init_data(t_data *data, int ac, char **av);


#endif