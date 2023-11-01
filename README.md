



each philosopher is implemented as a thread, 
each  forks are implemented as semaphores. 
Each philosopher thinks for a random amount of time, waits to pick up the forks in the correct order, eats for a random amount of time, and repeats. 

The philosopher repeats three actions:
eating ➔ sleeping ➔ thinking.








# 42 Philosophers

This project is a simulation of the dining philosophers problem, a classic synchronization and concurrency problem. It involves multiple philosophers who must share a limited number of forks to dine, but they must do so in a way that avoids deadlocks and ensures that they can eat without conflicts.

## Introduction

In this project, each philosopher is implemented as a thread, and each fork is implemented as a semaphore. Each philosopher goes through a cycle of three actions: eating, sleeping, and thinking. The goal is to create a solution that allows the philosophers to dine without any of them starving or causing a deadlock.


each philosopher is implemented as a thread, 
each  forks are implemented as semaphores. 
Each philosopher thinks for a random amount of time, waits to pick up the forks in the correct order, eats for a random amount of time, and repeats. 

The philosopher repeats three actions:
eating ➔ sleeping ➔ thinking.

## Key Concepts

### Mutex

A mutex (short for mutual exclusion) is a synchronization mechanism used to control access to shared resources in a multi-threaded environment. It ensures that only one thread can access a critical section of code at a time, preventing data corruption and race conditions.

### Threads

Threads are the smallest units of a program that can be scheduled to run by the operating system. In the context of multi-threading, they allow a program to execute multiple tasks concurrently. In the "42 philosophers" project, each philosopher is implemented as a thread.

### Deadlock

Deadlock is a situation in which two or more threads or processes are unable to proceed because each is waiting for the other to release a resource. It's a critical issue in concurrent programming and can lead to system-wide stalls.

### Semaphore

A semaphore is a synchronization primitive that is used to control access to resources in a multi-threaded environment. Semaphores allow threads to coordinate and communicate with each other, preventing race conditions and ensuring orderly access to shared resources.

## Additional Information

You can find more documentation and helpful resources for this project on the following GitHub repositories:

- [Maria Lavrenova's 42 Philosophers Documentation](https://github.com/lavrenovamaria/42-philosophers)
- [Lazy Philosophers Tester](https://github.com/MichelleJiam/LazyPhilosophersTester)



## Usage

```C
int usage(void)
{
    static char usage_str[] =
    
    GREEN"philo_one\n"RESET
    "Simulation of the philosopher.\n\n"
    YELLOW"USAGE:\n    "RESET
    GREEN"philo_one "RESET
    "number_of_philosopher time_to_die time_to_eat "
    "time_to_sleep [number_of_time_each_philosophers_must_eat]\n\n"
    YELLOW"ARGS:\n    "RESET
    "All args must be positive integers\n";
    ft_putstr_fd(usage_str, 1);
    return (1);
}

## Resources

...
## Additional Information

You can find more documentation and helpful resources for this project on the following GitHub repositories:

- [Maria Lavrenova's 42 Philosophers Documentation](https://github.com/lavrenovamaria/42-philosophers)
- [Lazy Philosophers Tester](https://github.com/MichelleJiam/LazyPhilosophersTester)

Feel free to explore these resources to gain a deeper understanding of the concepts and solutions related to the dining philosophers problem in the context of the 42 Cursus.

Enjoy solving this classic synchronization problem!



Tester
https://github.com/MichelleJiam/LazyPhilosophersTester
