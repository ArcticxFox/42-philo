/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:38:26 by ejones            #+#    #+#             */
/*   Updated: 2026/04/07 18:37:57 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	print_format(void)
{
	printf("./philo <nb_of_philos> <time_to_die> ");
	printf("<time_to_eat> <time_to_sleep> <number of meals to eat>\n");
	printf("./philo <nb_of_philos> <time in ms> ");
	printf("<time in ms> <time in ms> <number of meals to eat>\n");
}

static int	ft_isnb(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		print_format();
		return (EXIT_FAILURE);
	}
	while (i < ac)
	{
		if (ft_isnb(av[i]) != 0)
		{
			print_format();
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
