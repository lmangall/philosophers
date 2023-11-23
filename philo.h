
#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>
# include <stdbool.h>


typedef struct s_philo 
{
	struct s_data	*data;      /**< Pointer to the data struct. */
	int				id;			/**< Philosopher's unique identifier. */
	int				eat_cont; 	/**< Number of times the philosopher has eaten. */
	int				eating; 	/**< Flag indicating if the philosopher is currently eating. */
	int             dead_or_alive; /**< Flag indicating if the philosopher is currently dead or alive. */
    // pthread_mutex_t    *fork_l;	/**< Philosopher's left fork. */
    // pthread_mutex_t    *fork_r;	/**< Philosopher's right fork. */
    int             fork_l;     /**< Philosopher's left fork. */
    int             fork_r;     /**< Philosopher's right fork. */
    uint64_t        last_eat;	/**< Time in milliseconds when the philosopher last ate. */
    // uint64_t		time_to_die;/**< Time in milliseconds before a philosopher dies if they haven't eaten. */
	pthread_t		t1;			/**< Philosopher's thread. */
    pthread_t       eat;        /**< Philosopher's thread. */
	pthread_mutex_t	lock;		/**< Mutex lock for this philosopher's state. */
} t_philo;


typedef struct s_data 
{
    int				nb_philo;	/**< Number of philosophers in the simulation. */
    int				nb_eat;		/**< Number times each philo must eat (optional). */
    int             nb_ate;     /**< Number of philosopher who has eaten all his meals */
    int             dead_phi;   /**< Number of philosophers that are dead */
    int             finished;
    int             thread_nbr;
    int             *threads;
    int             death_thread_id;
    int             printed_end;
    uint64_t		start_time;	/**< Time when the simulation started. */
    uint64_t		tto_die;	/**< Time in milliseconds before a philosopher dies if they haven't eaten. */
    uint64_t		tto_eat;	/**< Time in milliseconds required for a philosopher to eat. */
    uint64_t		tto_sleep;	/**< Time in milliseconds required for a philosopher to sleep. */
    t_philo			*philos;	/**< Array of philosophers. */
    pthread_t		*death_thread;         /**< Philosopher's thread. */
    //pthread_t       *threads;	/**< Philosopher's thread. */
    pthread_mutex_t	*forks;		/**< Array of mutex locks for the forks. */
    pthread_mutex_t	*lock;		/**< Mutex lock for controlling access to shared data. */
    pthread_mutex_t *write;		/**< Mutex lock for writing to stdout. */
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

void    *check_meals(void *philo_pointer);
void    a_table(t_data *data);
void	free_n_exit(t_data *data);

//                                in init.c :
void	distrib_forks(t_philo *philo);
void    init_forks(t_data *data);
void    init_philo(t_data *data);
void    init_data(t_data *data, int ac, char **av);


//                                in days_n_night

void *eat(void *philo_pointer);
void *routine(void *arg);

int 	meal_tracker(t_philo *philo);


void	delay(uint64_t start_time);
int output(t_philo *philo, int status);
void *check_death_or_meals(void *data_pointer);
int death(t_data *data);

//                                in utils.c :
int		    ft_atoi(const char *str);
int         finish(t_data *data);
/**
 * @brief Sleeps for a specified amount of time.
 *
 * This function puts the calling thread to sleep for the specified time duration.
 * It uses a busy-wait loop to ensure accurate sleep time.
 *
 * @param time The duration to sleep in microseconds.
 * @ingroup time_utils
 */
void ft_usleep(uint64_t time);
/**
 * @brief Gets the current time in milliseconds.
 *
 * This function retrieves the current time using the gettimeofday system call
 * and returns it in milliseconds.
 *
 * @return The current time in milliseconds.
 * @ingroup time_utils
 */
uint64_t get_time(void);



#endif