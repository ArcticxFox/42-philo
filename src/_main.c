/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:30:53 by ejones            #+#    #+#             */
/*   Updated: 2026/04/07 18:44:42 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

//always free forks before hand =>=>: destroy_and_free()
static void	free_allocs(t_args *args)
{
	destroy_and_free(args, args->forks, args->nbr_philos);
}

int	main(int ac, char **av)
{
	t_args	args;
	int		i;

	i = 0;
	memset(&args, 0, sizeof(t_args));
	args.start_of_prog = get_time_ms();
	if (ft_check_args(ac, av) != 0)
		return (1);
	if (init_struct(&args, av) != 0)
		return (2);
	if (create_threads(&args))
		free_allocs(&args);
	pthread_join(args.monitor, NULL);
	while (i < args.nbr_philos)
		pthread_join(args.philos[i++].thread, NULL);
	free_allocs(&args);
	return (0);
}
