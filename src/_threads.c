/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _threads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:03:21 by ejones            #+#    #+#             */
/*   Updated: 2026/04/01 17:25:57 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	get_death(t_args *args)
{
	int	val;

	pthread_mutex_lock(&args->death_mutex);
	val = args->death;
	pthread_mutex_unlock(&args->death_mutex);
	return (val);
}

void	set_death(t_args *args)
{
	pthread_mutex_lock(&args->death_mutex);
	args->death = 1;
	pthread_mutex_unlock(&args->death_mutex);
}

void	*thread_func(void *arg)
{
	t_philo		*philo;
	t_args		*args;
	short int	left;
	short int	right;

	philo = (t_philo *)arg;
	args = philo->args;
	left = philo->id;
	right = (philo->id + 1) % args->nbr_philos;
	while (!get_death(args))
	{
		if (ft_eating(philo, left, right))
			break ;
		if (ft_sleeping(philo))
			break ;
		print_action(philo, "is thinking");
		usleep((args->time_to_die - args->time_to_eat - args->time_to_sleep) * 500);
	}
	return (NULL);
}

void	*thread_monitor(void *arg)
{
	int		i;
	time_t	lastmeal;
	t_args	*args;
	t_philo	*philos;

	args = (t_args *)arg;
	philos = args->philos;
	while (!get_death(args))
	{
		i = 0;
		while (i < args->nbr_philos)
		{
			pthread_mutex_lock(&args->meals_mutex[i]);
			lastmeal = philos[i].last_meal;
			pthread_mutex_unlock(&args->meals_mutex[i]);
			if (!philos_not_full(args))
			{
				set_death(args);
				return (NULL);
			}
			if (get_time_ms() - lastmeal > args->time_to_die)
			{
				set_death(args);
				print_action(&philos[i], "died");
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philos)
	{
		args->philos[i].id = i;
		args->philos[i].meals_count = 0;
		args->philos[i].last_meal = args->start_of_prog;
		args->philos[i].args = args;
		if (pthread_create(&args->philos[i].thread, NULL, thread_func,
			&args->philos[i]) != 0)
		{
			printf("A Philo %d pthread_create FAILED\n", i);
			set_death(args);
			while (--i >= 0)
				pthread_join(args->philos[i].thread, NULL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_create(&args->monitor, NULL, thread_monitor, args) != 0)
	{
		printf("monitoring thread creation failed\n");
		i = args->nbr_philos;
		while (--i >= 0)
			pthread_join(args->philos[i].thread, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

