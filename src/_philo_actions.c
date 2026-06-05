/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:20:32 by ejones            #+#    #+#             */
/*   Updated: 2026/06/05 17:08:10 by ejones           ###   ########.fr       */
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
		printf("%zu %d died\n", timestamp, philo->id + 1);
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
	if (philo->args->nbr_philos == 1)
	{
		pthread_mutex_lock(&philo->args->forks[left]);
		print_action(philo, "has taken a fork");
		while (!get_death(philo->args))
			usleep(200);
		pthread_mutex_unlock(&philo->args->forks[left]);
		return (EXIT_FAILURE);
	}
	ft_lock(philo, left, right);
	start = get_time_ms();
	meal_mutex(philo, 0);
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
	meal_mutex(philo, 1);
	return (EXIT_SUCCESS);
}

int	ft_sleeping(t_philo *philo)
{
	time_t	start;
	time_t	time_to_sleep;

	if (get_death(philo->args))
		return (EXIT_FAILURE);
	start = get_time_ms();
	time_to_sleep = philo->args->time_to_sleep;
	print_action(philo, "is sleeping");
	while (get_time_ms() - start < time_to_sleep)
	{
		if (get_death(philo->args))
			return (EXIT_FAILURE);
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

int	ft_thinking(t_philo *philo, time_t time)
{
	time_t	start;
	time_t	time_to_think;

	if (get_death(philo->args))
		return (EXIT_FAILURE);
	start = get_time_ms();
	time_to_think = ((philo->args->time_to_die - time - 1000) * 500);
	print_action(philo, "is thinking");
	while (get_time_ms() - start < time_to_think)
	{
		if (get_death(philo->args))
			return (EXIT_FAILURE);
		usleep(200);
	}
	return (EXIT_SUCCESS);
}
