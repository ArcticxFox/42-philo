/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init_args_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:31:30 by ejones            #+#    #+#             */
/*   Updated: 2026/04/01 17:15:23 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	destroy_and_free(t_args *args, pthread_mutex_t *ptr, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&ptr[i]);
		i++;
	}
	if (args->forks)
		free(args->forks);
	if (args->philos)
		free(args->philos);
}

static int	init_mutex(t_args *args, pthread_mutex_t *ptr)
{
	if (pthread_mutex_init(ptr, NULL) != 0)
	{
		destroy_and_free(args, ptr, 1);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	init_forks_meals_mutex(t_args *args)
{
	int	i;

	i = -1;
	args->forks = malloc(args->nbr_philos * sizeof(pthread_mutex_t));
	while (++i < args->nbr_philos)
	{
		if (pthread_mutex_init(&(args->forks)[i], NULL) != 0)
		{
			destroy_and_free(args, args->forks, i);
			return (EXIT_FAILURE);
		}
	}
	args->meals_mutex = malloc(args->nbr_philos * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < args->nbr_philos)
	{
		if (pthread_mutex_init(&args->meals_mutex[i], NULL) != 0)
		{
			destroy_and_free(args, args->forks, args->nbr_philos);
			destroy_and_free(args, args->meals_mutex, i);
			free(args->meals_mutex);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	init_mutexes(t_args *args)
{
	if (init_forks_meals_mutex(args) != 0)
		return (EXIT_FAILURE);
	if (init_mutex(args, &args->print_mutex) != 0)
	{
		destroy_and_free(args, args->forks, args->nbr_philos);
		destroy_and_free(args, args->meals_mutex, args->nbr_philos);
		free(args->meals_mutex);
		return (EXIT_FAILURE);
	}
	if (init_mutex(args, &args->death_mutex) != 0)
	{
		destroy_and_free(args, args->forks, args->nbr_philos);
		destroy_and_free(args, args->meals_mutex, 1);
		free(args->meals_mutex);
		destroy_and_free(args, &args->print_mutex, 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_struct(t_args *args, char **av)
{
	args->nbr_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->min_to_eat = ft_atoi(av[5]);
	else
		args->min_to_eat = -1;
	if (args->nbr_philos < 1 || args->time_to_die < 1 || args->time_to_eat < 1
		|| args->time_to_sleep < 1 || args->min_to_eat == 0
		|| (args->min_to_eat < -1))
	{
		printf("The arguments need to be superior to 0\n");
		return (EXIT_FAILURE);
	}
	args->philos = malloc(args->nbr_philos * sizeof(t_philo));
	if (!args->philos)
		return (EXIT_FAILURE);
	memset(args->philos, 0, args->nbr_philos * sizeof(t_philo));
	if (init_mutexes(args) != 0)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
