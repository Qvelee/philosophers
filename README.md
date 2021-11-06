# philosophers

This project represents the solution of [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), but with any number of philosphers.

### Description

Each directory "philo_*" contains solution with some differences in approach:

 • philo_one - using threads and mutexes
 
 • philo_two - using threads and semaphores
 
 • philo_three - using processes and semaphores.
 
### Build

  1) `cd` to philo_* directory;
  2) `make` creates executable named "philo_*number*".
 
 To remove all files created by program run `make fclean`, or `make clean` to remove all except executable.
 
### Usage

 Program arguments:
  `number_of_philosophers` `time_to_die` `time_to_eat` `time_to_sleep` `[number_of_times_each_philosopher_must_eat]`, time in ms.
 
 For example `./philo_one 4 500 100 100`

![ezgif com-gif-maker(4)](https://user-images.githubusercontent.com/36854467/140602711-d149ef78-d794-4cfe-ac9f-e6c6985072a5.gif)
