/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _threads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:03:21 by ejones            #+#    #+#             */
/*   Updated: 2026/04/07 19:37:03 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	*thread_func(void *arg)
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
		if (ft_thinking(philo, args->time_to_eat + args->time_to_sleep))
			break;
	}
	return (NULL);
}
static int	end_simulation(t_args *args, int i)
{
	time_t	lastmeal;
	t_philo	*philos;

	philos = args->philos;
	pthread_mutex_lock(&args->philos[i].meals_mutex);
	lastmeal = philos[i].last_meal;
	pthread_mutex_unlock(&args->philos[i].meals_mutex);
	if (!philos_not_full(args))
	{
		set_death(args);
		return (EXIT_FAILURE);
	}
	if (get_time_ms() - lastmeal > args->time_to_die)
	{
		set_death(args);
		print_action(&philos[i], "died");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	*thread_monitor(void *arg)
{
	int		i;
	t_args	*args;
	t_philo	*philos;

	args = (t_args *)arg;
	philos = args->philos;
	while (!get_death(args))
	{
		i = 0;
		while (i < args->nbr_philos)
		{
			if (end_simulation(args, i))
				return (NULL);
			i++;
		}
		usleep(200);
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

