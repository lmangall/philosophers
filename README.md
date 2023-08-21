# philosophers



https://42-cursus.gitbook.io/guide/rank-03/philosophers


```C
int	usage(void)
{
	static char usage_str[] =

	GREEN"philo_one\n"RESET
	"Simulation of the philosopher.\n\n"
	YELLOW"USAGE:\n    "RESET
	GREEN"philo_one "RESET
	"number_of_philosopher time_to_die time_to_eat "
	"time_to_sleep [number_of_time_each_philosophers_must_eat]\n\n"
	YELLOW"ARGS:\n    "RESET
	"All args must be positive integer\n";
	ft_putstr_fd(usage_str, 1);
	return (1);
}
```
from: https://github.com/agavrel/42_CheatSheet



https://github.com/lavrenovamaria/42-philosophers
https://www.geeksforgeeks.org/dining-philosophers-problem/
https://medium.com/science-journal/the-dining-philosophers-problem-fded861c37ed
https://www.chegg.com/homework-help/questions-and-answers/44-dining-philosophers-87[…]ilosophers-dining-philosophers-problem-proposed-dijk-q60256378
https://cse.buffalo.edu/faculty/tkosar/cse421-521_fall2012/slides/09-Process_Synchronization_II_2spp.pdf
http://web.cecs.pdx.edu/~harry/Blitz/version-1-0/InstructorInfo/DinPhilSolution.pdf
https://github.com/MichelleJiam/LazyPhilosophersTester
