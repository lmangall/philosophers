




vérifier la fonction check_args

in phi_sleep, philo is locked and in output the finished function try to lock it




To check the code with Valgrind:
clear && valgrind -s --tool=helgrind ./philosophers 4 200 60 60

To check the code with Fsanitize
add -fsanitize=thread to the compiler flags, then execute normally

Test cases:
./philosophers 1 800 200 200 => nobody dies
./philosophers 4 310 200 100 => should die
./philosophers 5 800 200 200 7 => should stop after eating 7 times


Example Command:
`./philosophers 5 800 200 200 7`

In this example, there are 5 philosophers, and the simulation is configured with the following parameters:
- `time_to_die`: 800 milliseconds
- `time_to_eat`: 200 milliseconds
- `time_to_sleep`: 200 milliseconds
- `number_of_times_each_philosopher_must_eat`: 7
The expected outcome is that no philosopher should die, and each philosopher should eat 7 times before the simulation stops.



https://github.com/abdeljalil-salhi/philosophers
https://github.com/clemedon/philosophers



# Learnings

With this implementation the dining philosophers problem I gained a deeper understanding of concurrent programming. This project provided me with insights into the challenges and complexities of managing shared resources, implementing mutexes and and addressing issues like deadlock and data races.

Implementing the dining philosophers problem was a hands-on experience that bridged the gap between theoretical knowledge and practical application.


### 42 Philosophers

This project is a simulation of the dining philosophers problem, a classic synchronization and concurrency problem. It involves multiple philosophers who must share a limited number of forks to dine, but they must do so in a way that avoids deadlocks and ensures that they can eat without conflicts.

## Introduction

In this project, each philosopher is implemented as a thread, and each fork is implemented as a semaphore. Each philosopher goes through a cycle of three actions: eating, sleeping, and thinking. The goal is to create a solution that allows the philosophers to dine without any of them starving or causing a deadlock.

Each philosopher thinks for a random amount of time, waits to pick up the forks in the correct order, eats for a random amount of time, and repeats. The philosopher repeats three actions: eating ➔ sleeping ➔ thinking.

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

Your program should take the following arguments:

- **number_of_philosophers:** The number of philosophers and also the number of forks.
- **time_to_die (in milliseconds):** If a philosopher hasn't started eating within time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- **time_to_eat (in milliseconds):** The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- **time_to_sleep (in milliseconds):** The time a philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat (optional argument):** If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

Each philosopher has a number ranging from 1 to number_of_philosophers. Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.


## Testing and Debugging

### Check with Valgrind

To check the code with Valgrind, use the following command:
```bash
clear && valgrind -s --tool=helgrind ./philosophers 4 200 60 60
```
### Check with Fsanitize
To check the code with Fsanitize, add -fsanitize=thread to the compiler flags, and then execute normally.

### Test Cases
Here are some test cases to verify the behavior of the program:
Case 1: Nobody dies : 
`./philosophers 1 800 200 200`
Case 2: A philo should die :
`./philosophers 4 310 200 100`
Case 3: Simulation stops after eating 7 times
`./philosophers 5 800 200 200 7` :
Adjust the command-line arguments as needed for your specific test scenarios.
