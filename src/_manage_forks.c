/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _manage_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:19:30 by ejones            #+#    #+#             */
/*   Updated: 2026/04/01 17:19:31 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

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
