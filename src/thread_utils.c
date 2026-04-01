/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:53:47 by ejones            #+#    #+#             */
/*   Updated: 2026/04/01 17:19:15 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

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
		pthread_mutex_lock(&args->meals_mutex[i]);
		meal_count = args->philos[i].meals_count;
		pthread_mutex_unlock(&args->meals_mutex[i]);
		if (meal_count >= args->min_to_eat)
			nbr_philos_full += 1;
		i++;
	}
	if (nbr_philos_full == args->nbr_philos)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
