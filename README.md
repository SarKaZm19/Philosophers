# Philosophers

An implementation of the classic **Dining Philosophers** concurrency problem in C, developed as part of the 42 curriculum.

The project focuses on synchronization, timing and shared-resource management: several philosophers compete for forks while a monitor must detect starvation without introducing race conditions or deadlocks.

## Implementations

### Mandatory — threads and mutexes

Each philosopher runs as a thread. Forks are represented by mutexes, with shared state protected against concurrent access.

### Bonus — processes and semaphores

The bonus version uses separate processes and POSIX semaphores, with a monitoring thread inside each philosopher process.

## Build

Mandatory version:

```bash
cd philo
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```

Bonus version:

```bash
cd philo_bonus
make
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```

Example:

```bash
./philo 5 800 200 200
```

## Core challenges

- Coordinating access to shared forks
- Avoiding deadlocks
- Preventing data races
- Keeping timing sufficiently precise
- Detecting philosopher death correctly
- Stopping the simulation cleanly
- Handling edge cases such as a single philosopher
- Reworking the synchronization model from mutexes to semaphores for the bonus version

## What this project demonstrates

Philosophers is a compact project with a deceptively difficult problem underneath. It was a practical introduction to concurrency primitives and to the fact that code can be logically correct in isolation while still failing because of execution order and shared state.

---

Part of my developer portfolio: **[github.com/Overflow-ADW](https://github.com/Overflow-ADW)**  
Professional work: **[Avenue du Web](https://avenueduweb.be)**
