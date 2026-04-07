/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:53:47 by ejones            #+#    #+#             */
/*   Updated: 2026/04/07 18:48:15 by ejones           ###   ########.fr       */
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

time_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	philos_not_full(t_args *args)
{
	int	i;
	int	meal_count;
	int	nbr_philos_full;

	i = 0;
	meal_count = 0;
	nbr_philos_full = 0;
	if (args->min_to_eat == -1)
		return (EXIT_FAILURE);
	while (i < args->nbr_philos)
	{
		pthread_mutex_lock(&args->philos[i].meals_mutex);
		meal_count = args->philos[i].meals_count;
		pthread_mutex_unlock(&args->philos[i].meals_mutex);
		if (meal_count >= args->min_to_eat)
			nbr_philos_full += 1;
		i++;
	}
	if (nbr_philos_full == args->nbr_philos)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
