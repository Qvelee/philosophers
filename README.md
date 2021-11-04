# philosophers

This project represents the solution of [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), but with any number of philosphers.

> **Description**

Each directory _philo_*_ contains solution with some differences in approach:
 • philo_one - using threads and mutexes;
 • philo_two - using threads and semaphores;
 • philo_three - using processes and semaphores.
 
> **Build**

  1) `cd` to philo_* directory;
  2) `make` creates executable file named "philo_*number*".
 
 To remove all files created by program enter `make fclean`, or `make clean` to remove all except executable.
 
> **Usage**

 Program arguments:
  `number_of_philosophers` `time_to_die` `time_to_eat` `time_to_sleep` `[number_of_times_each_philosopher_must_eat]`, time in ms.
