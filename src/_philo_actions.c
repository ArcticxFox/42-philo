/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:20:32 by ejones            #+#    #+#             */
/*   Updated: 2026/04/01 16:24:42 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	print_action(t_philo *philo, char *str)
{
	time_t	timestamp;

	pthread_mutex_lock(&philo->args->print_mutex);
	timestamp = get_time_ms() - philo->args->start_of_prog;
	if (ft_strcmp(str, "died") == 0)
	{
		printf("%zu %d died\n", timestamp, philo->id);
	}
	else if (!get_death(philo->args))
	{
		if (get_death(philo->args))
		{
			pthread_mutex_unlock(&philo->args->print_mutex);
			return ;
		}
		printf("%zu %d %s\n", timestamp, philo->id, str);
	}
	pthread_mutex_unlock(&philo->args->print_mutex);
}

int	ft_eating(t_philo *philo, short int left, short int right)
{
	time_t	start;

	if (get_death(philo->args))
		return (EXIT_FAILURE);
	ft_lock(philo, left, right);
	start = get_time_ms();
	pthread_mutex_lock(&philo->args->meals_mutex[philo->id]);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->args->meals_mutex[philo->id]);
	print_action(philo, "is eating");
	while (get_time_ms() - start < philo->args->time_to_eat)
	{
		if (get_death(philo->args))
		{
			ft_unlock(philo, left, right);
			return (EXIT_FAILURE);
		}
		usleep(200);
	}
	ft_unlock(philo, left, right);
	pthread_mutex_lock(&philo->args->meals_mutex[philo->id]);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->args->meals_mutex[philo->id]);
	return (EXIT_SUCCESS);
}

int	ft_sleeping(t_philo *philo)
{
	time_t	start;
	time_t	time_to_sleep;

	start = get_time_ms();
	time_to_sleep = philo->args->time_to_sleep;
	if (get_death(philo->args))
		return (EXIT_FAILURE);
	print_action(philo, "is sleeping");
	while (get_time_ms() - start < time_to_sleep)
	{
		if (get_death(philo->args))
			return (EXIT_FAILURE);
		usleep(200);
	}
	return (EXIT_SUCCESS);
}
