#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct timeval	t_timeval;

typedef enum	e_state
{
	DEAD = 1,
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_args	t_args;

typedef struct	s_philo
{
	int			id;
	size_t		meals_count;
	time_t		last_meal;
	pthread_t	thread;
	t_args		*args;
}	t_philo;

typedef struct	s_args
{
	int				nbr_philos;
	int				min_to_eat;	// max nbr meals to eat
	int				death;
	time_t			time_to_die;	// max time to pass before death
	time_t			time_to_eat;	// time needed to eat
	time_t			time_to_sleep;	// time needed to sleep
	time_t			start_of_prog;	// start time of launch
	t_philo			*philos;		//malloc the number of philos
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meals_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_args;

void		ft_lock(t_philo *philo, int left, int right);
void		ft_unlock(t_philo *philo, int left, int right);

time_t		elapsed_time(struct timeval start);

// New functions
int			ft_check_args(int ac, char **av);
int			init_struct(t_args *args, char **av);
time_t		get_time_ms(void);
void		destroy_and_free(t_args *args, pthread_mutex_t *ptr, int max);

//_threads.c
int		get_death(t_args *args);
int		create_threads(t_args *args);

//_philo_actions.c
void	print_action(t_philo *philo, char *str);
int		ft_eating(t_philo *philo, short int left, short int right);
int		ft_sleeping(t_philo *philo);

//utils.c
int	ft_isdigit(int c);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_atoi(const char *nptr);

#endif
