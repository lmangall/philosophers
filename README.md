











in phi_sleep, philo is locked and in output the finished function try to lock it











clear && valgrind -s --tool=helgrind ./philosophers 4 200 60 60


--tool=drd

4 310 200 100 = die


valgrind -q --leak-check=yes --show-leak-kinds=all ./philosophers 4 310 200 100


valgrind --leak-check=yes --show-leak-kinds=all ./philosophers 4 310 200 100


printf("Thread %lu in check_death_or_meals\n", pthread_self());





https://github.com/abdeljalil-salhi/philosophers
https://github.com/clemedon/philosophers






<img width="1309" alt="Screenshot 2023-11-02 at 11 48 12" src="https://github.com/lmangall/philosophers/assets/107299611/d917c3bc-ae0c-4b16-95ca-2c1a34dbddbf">
<img width="1127" alt="Screenshot 2023-11-02 at 11 49 59" src="https://github.com/lmangall/philosophers/assets/107299611/8a044af0-f313-47b7-9c9b-21b6d0f6d04a">




SCHEDULER



good info on testing and debugging:
https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/



each philosopher is implemented as a thread, 
each  forks are implemented as semaphores. 
Each philosopher thinks for a random amount of time, waits to pick up the forks in the correct order, eats for a random amount of time, and repeats. 

The philosopher repeats three actions:
eating ➔ sleeping ➔ thinking.



Youtube playlist:
https://www.youtube.com/watch?v=kCGaRdArSnA&list=PLGU1kcPKHMKi41Py2kqxdvqYE3M9VhCHe&ab_channel=CodeVault

on Codevault:
What is a mutex ? (pthread_mutex)
What are Threads
What is a race condition

github with explanation:
https://github.com/TommyJD93/Philosophers


pthread_create: This function is used in a multi-threaded program to create a new thread. It takes several arguments, including a pointer to a thread identifier, attributes for the new thread, the function the thread should execute, and the arguments to be passed to that function. Once called, it creates a new thread that starts executing the specified function concurrently with the calling thread.

pthread_join: This function is used to wait for a specific thread to complete its execution. When you call pthread_join on a thread, the calling thread will block until the specified thread finishes. It also allows you to retrieve the return value of the joined thread. This is commonly used to synchronize threads and ensure that the main program or another thread waits for the completion of a specific task before proceeding.





A pthread_mutex_t is a synchronization mechanism in the POSIX threads library used to prevent race conditions in multi-threaded programs. It allows threads to lock and unlock critical sections of code, ensuring that only one thread can access them at a time, thus preventing data corruption and race conditions.

Lock: Locking a mutex means that a thread acquires ownership of the mutex, which indicates that it is entering a critical section of code. When a thread locks a mutex, it ensures that other threads attempting to lock the same mutex will be blocked until the mutex is unlocked.

Unlock: Unlocking a mutex means that a thread releases ownership of the mutex, indicating that it is leaving the critical section. When a thread unlocks a mutex, it allows other threads to potentially acquire ownership of the mutex and enter the critical section.

pthread_mutex_lock(&mutex)
pthread_mutex_unlock(&mutex)












```C
// pthread_create
pthread_t thread_id;
pthread_create(&thread_id, NULL, start_routine, argument);

```

```C
// pthread_join
pthread_join(thread_id, &return_value);

```



```C

```








---



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
```

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
