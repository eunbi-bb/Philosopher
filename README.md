# Philosopher
*This project is about learning how to create threads and discovering with the Dining philosophers problem. It is set up as follows:*
- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively **eat**, **think**, or **sleep**. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping;and, of course, while sleeping, they are not eating nor thinking.
- There are **as many forks as philosophers**.
- A philosopher takes their right and their left forks to eat, one in each hand to eat.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation **stops when a philosopher dies of starvation**.
- The philosophers cannot communicate each other. 
- No need to say that philosophers should avoid dying!

![Minishell(2)](https://github.com/eunbi-bb/minishell/assets/80834766/4094a97b-8482-4c0d-9f4a-c4b77c219a0d)

## Usage
```
$ make
```
```
./philo 5 800 200 200
```

### Input
```
./philo "number_of_philosophers" "time_to_die" "time_to_eat "time_to_sleep" [number_of_time_each_philosopher_must_eat]
```


| Argument                | Explanation                                                                                                                                                    |
| ----------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `number_of_philosophers`    | The number of philosophers.                                                                                                                        |
| `time_to_die`           | If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die. |
| `time_to_eat`           | The time it takes for a philosopher to eat. During that time, they will need to hold two forks.                                                                                                                |
| `time_to_sleep`         | The time a philosopher will spend sleeping.                                                                                                              |
| [optional]<br>`number_of_time_each_philosopher_must_eat` | If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.              |

### Simulation
Without option [number_of_time_each_philosopher_must_eat].
```
[time_stamp_in_millisecond] philospher [n] grabbed a fork from left.
[time_stamp_in_millisecond] philospher [n] grabbed a fork from right.
[time_stamp_in_millisecond] philospher [n] is eating spaghetti.
[time_stamp_in_millisecond] philospher [n] is sleeping.
[time_stamp_in_millisecond] philospher [n] died.
```
With option [number_of_time_each_philosopher_must_eat].
```
./pilo "n" "time_to_die" "time_to_eat "time_to_sleep" [x]
```
```
[time_stamp_in_millisecond] philospher [n] grabbed a fork from left.
[time_stamp_in_millisecond] philospher [n] grabbed a fork from right.
[time_stamp_in_millisecond] philospher [n] is eating spaghetti. (1 times)
[time_stamp_in_millisecond] philospher [n] is sleeping.
.
.
.
[time_stamp_in_millisecond] philospher [n] is eating spaghetti. (x times)
```
**Commands to try**
- No philosopher should die and the program should continue indefinitely.
```
./philo 100 810 200 200
```
- No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
```
./philo 5 800 200 200 7
```
- The philosopher should not eat and should die.
```
./philo 1 800 200 200
```
- No philosopher should die and the program should continue indefinitely.
```
./philo 4 200 205 200
```

## About Mutex
A mutex (short for "mutual exclusion") is a synchronization mechanism used in **multi-threaded environments to ensure exclusive access to shared resources**. \
It typically employs a boolean or integer variable to represent the lock's state, \
where "locked" indicates that a thread holds the resource, and "unlocked" signifies that it's available.

When a thread attempts to acquire a mutex and finds it locked by another thread, it gets blocked, awaiting its turn. \
**Only the thread that successfully acquires the mutex can unlock** it when it's done using the shared resource. \
This exclusive locking and unlocking mechanism prevents concurrent access by multiple threads, ensuring data integrity and preventing conflicts in multi-threaded programs.

### Solution for Data races
In the Dining Philosophers problem, data races can occur when multiple philosophers concurrently access shared data, leading to unpredictable outcomes. \
To prevent this, two mutexes are employed:

- Mutex for Beginning and End of Eating Time:
Ensures exclusive access to the time variables of eating (set_pasta_time and last_pasta_time).\
Philosophers must acquire this mutex before reading or updating the variable, preventing concurrent access.

- Mutex for Status Check:
Safeguards the status of a thread, which signifies a philosopher's death.\
Access to this variable is controlled by acquiring the mutex, ensuring that only one thread at a time can check or modify it.

These mutexes, along with associated helper functions for reading and writing data, maintain thread safety in the Dining Philosophers problem, preventing data races and ensuring program correctness.
