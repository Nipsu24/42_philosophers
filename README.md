<h1 align="center">philosophers</h1>

> Hive Helsinki (School 42) 8th project (Rank03/06) of core curriculum.

<h2 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#program">Program</a>
	<span> · </span>
	<a href="#requirements">Requirements</a>
	<span> · </span>
	<a href="#instructions">Instructions</a>
</h2>

## About
The project's executable starts a simulation based on the dining philosophers problem, in which x amount of philosophers sit around a table and repeatedly eat, sleep and think.
Eating is only possible if a philosopher can aquire two forks, whereby there are only as many forks as philosophers present at the table. If a philosopher could not manage to eat in
a specified time, he dies. The aim of the program is to avoid the death of any philosopher, whereby a certain combination of the provided parameters ultimately leads to the death of a philosopher (e.g. if "time to die" is shorter than the combined "time to eat" and "time to sleep,"). The project familiarises oneself with the concept of threading processes and protecting code blocks against deadlocks and data races by mutexes.

## Program
Running the executable by passing the required arguments runs the simulation and displays the respective actions in the terminal (time in ms, index of the philosopher and the action). Several mutexes (including the left and right fork for each philosopher) for avoiding deadlocks and data races were initialised in the program code. Also, threads for each
philosopher and a thread for an observer were created, whereby the philosophers pursue their different routines and the observer checks if all philosophers have eaten their meals
or if any has died.

## Requirements
- `gcc` compiler

## Instructions

### 1. Compiling the program

To compile the files cd into the `philo` directory run the following command:

```
$ make 
```

### 2. Start the simulation

The simulation can be started by passing the executable the following arguments:
amount of philos
time to die (in ms)
time to eat (in ms)
time to sleep (in ms)
number of times each philosopher eats (optional)
e.g.:
```
$ ./philo 5 300 100 100 10
```
