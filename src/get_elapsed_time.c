/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elapsed_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:13:21 by ejones            #+#    #+#             */
/*   Updated: 2026/04/01 17:13:22 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

time_t	elapsed_time(struct timeval start)
{
	struct timeval	end;
	time_t			elapsed;

	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000;
	return (elapsed);
}

time_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
