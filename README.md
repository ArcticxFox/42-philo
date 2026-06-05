*This project has been created as part of the 42 curriculum by ejones*

# 42-philo

- ## 1. Description

	The goal of this project is to simulate using threads the philosophers problem. \
	The problem is as follows:
	-	One or more philosophers sit at a round table.
		There is a large bowl of spaghetti in the middle of the table.
	-	The philosophers take turns eating sleeping and thinking. They perform those actions in the order as cited above. Philosophers can only perform one action at a time.
	-	In oder to eat, a philosopher needs 2 forks. there are as many forks as philophers
	-	A philosopher must pick up both the fork to their right and the fork to their left before eating.
	-	When they finish eating they put their forks down so that other philo can pick them up.
	-	The simulation stops when a philosopher dies of starvation.
	-	Every philosopher needs to eat and should never starve.
	-	Philosophers do not communicate with each other.
	-	Philosophers do not know if another philosopher is about to die.
	-	Needless to say, philosophers should avoid dying!

- ## 2. Instructions

	- ### 2.1 Makefile commands

		make - to compile \
		make bonus - to compile bonuses \
		make clean - to remove object files \
		make fclean - uses clean, then removes libraries \
		make re - uses fclean, and recompiles th whole project \

	- ### 2.2 Execution
		```yaml
		./philo <nb_of_philos> <time_to_die> "<time_to_eat> <time_to_sleep>
		```
		```yaml
		./philo <nb_of_philos> <time_to_die> "<time_to_eat> <time_to_sleep> <number_of_meals_to_eat>
		```
		**_<number_of_meals_to_eat>_** is optional
- ## Resources
	links :
	- [Undetsanding threads](https://franckh.developpez.com/tutoriels/posix/pthreads/)

	ChatGPT was mostly used for debugging and understanding how the thread functions worked.
