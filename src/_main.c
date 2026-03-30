/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:30:53 by ejones            #+#    #+#             */
/*   Updated: 2026/03/30 12:20:40 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

//always free forks before hand =>=>: destroy_and_free()
void	free_allocs(t_args *args)
{
	destroy_and_free(args, args->forks, args->nbr_philos);
	destroy_and_free(args, args->meals_mutex, args->nbr_philos);
	if (args->meals_mutex)
		free(args->meals_mutex);
}

int	main(int ac, char **av)
{
	t_args	args = {0};
	int		i = 0;

	memset(&args, 0, sizeof(t_args));
	args.start_of_prog = get_time_ms();
	if (ft_check_args(ac, av) != 0)
		return (1);
	if (init_struct(&args, av) != 0)
		return (2);
	if (create_threads(&args))
		free_allocs(&args);

//waiting for the end of threads
	pthread_join(args.monitor, NULL);
	while (i < args.nbr_philos)
		pthread_join(args.philos[i++].thread, NULL);
	return (0);
}
	// printf("%d\n", args.nbr_philos);
	// printf("%d\n", args.min_to_eat);
	// printf("%d\n", args.death);
	// printf("%zu\n", args.time_to_die);
	// printf("%zu\n", args.time_to_eat);
	// printf("%zu\n", args.time_to_sleep);
	// usleep(250 * 1000);
	// args.start_of_prog = get_time_ms() - args.start_of_prog;
	// printf("%zu\n", args.start_of_prog);
