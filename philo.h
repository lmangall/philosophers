#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#define FORK_1  0
#define FORK_2  1
#define EAT     2
#define SLEEP   3
#define THINK   4
#define DIED    5
#define ALL     6

typedef struct s_philo {
    struct s_data   *data;           /**< Pointer to the data struct. */
    int             id;              /**< Philosopher's unique identifier. */
    int             eat_cont;        /**< Number of times the philosopher has eaten. */
    int             eating;          /**< Flag indicating if the philosopher is currently eating. */
    int             dead_or_alive;   /**< Flag indicating if the philosopher is currently dead or alive. */
    int             fork_l;          /**< Philosopher's left fork. */
    int             fork_r;          /**< Philosopher's right fork. */
    uint64_t        last_eat;        /**< Time in milliseconds when the philosopher last ate. */
    uint64_t        tto_die;         /**< Time in milliseconds when the philosopher last ate. */
    pthread_t       *t1;             /**< Philosopher's thread. */
    pthread_t       *eat;            /**< Philosopher's thread. */
    pthread_mutex_t lock;            /**< Mutex lock for this philosopher's state. */
} t_philo;

typedef struct s_data {
    int             nb_philo;        /**< Number of philosophers in the simulation. */
    int             nb_eat;          /**< Number times each philo must eat (optional). */
    int             nb_ate;          /**< Number of philosopher who has eaten all his meals */
    int             dead_phi;        /**< Number of philosophers that are dead */
    int             finished;
    int             thread_nbr;
    int             *threads;
    int             death_thread_id;
    int             printed_end;
    uint64_t        start_time;      /**< Time when the simulation started. */
    uint64_t        tto_die;         /**< Time in milliseconds before a philosopher dies if they haven't eaten. */
    uint64_t        tto_eat;         /**< Time in milliseconds required for a philosopher to eat. */
    uint64_t        tto_sleep;       /**< Time in milliseconds required for a philosopher to sleep. */
    t_philo         *philos;         /**< Array of philosophers. */
    pthread_t       *death_thread;   /**< Philosopher's thread. */
    pthread_t       *meals;
    pthread_mutex_t *forks;          /**< Array of mutex locks for the forks. */
    pthread_mutex_t lock;            /**< Mutex lock for controlling access to shared data. */
    pthread_mutex_t write;           /**< Mutex lock for writing to stdout. */
    pthread_mutex_t dead_phi_lock;
} t_data;

int check_args(char **av);

void *check_meals(void *philo_pointer);
void a_table(t_data *data);
void free_n_exit(t_data *data);

// in init.c :
void distrib_forks(t_philo *philo);
void init_forks(t_data *data);
void init_philo(t_data *data);
void init_data(t_data *data, int ac, char **av);

// in days_n_night
int eat(void *philo_pointer);
int phi_sleep(t_philo *philo);
int think(t_philo *philo);
void *routine(void *philo_pointer);

int meal_tracker(t_philo *philo);

void delay(uint64_t start_time);
int output(t_philo *philo, int status);
void *check_death_or_meals(void *philo_pointer);
int death(t_data *data);

// in utils.c :
int ft_atoi(const char *str);
int finished(t_data *data);

// in utils_time.c :
void ft_usleep(uint64_t time);
uint64_t get_time(void);
void *check_all_ate(void *data_pointer);

// in utils_condition.c :
int must_die(t_philo *philo);
int all_ate(t_data *data);
int is_even(t_philo *philo);

#endif
