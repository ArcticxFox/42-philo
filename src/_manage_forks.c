/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _manage_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:19:30 by ejones            #+#    #+#             */
/*   Updated: 2026/06/05 16:49:38 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	meal_mutex(t_philo *philo, short int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&philo->args->philos[philo->id].meals_mutex);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo->args->philos[philo->id].meals_mutex);
		print_action(philo, "is eating");
	}
	if (i == 1 && philo->args->nbr_philos > 1)
	{
		pthread_mutex_lock(&philo->args->philos[philo->id].meals_mutex);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->args->philos[philo->id].meals_mutex);
	}
}

void	ft_lock(t_philo *philo, int left, int right)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->args->forks[right]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->args->forks[left]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->args->forks[left]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->args->forks[right]);
		print_action(philo, "has taken a fork");
	}
}

void	ft_unlock(t_philo *philo, int left, int right)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->args->forks[left]);
		pthread_mutex_unlock(&philo->args->forks[right]);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->forks[right]);
		pthread_mutex_unlock(&philo->args->forks[left]);
	}
}
