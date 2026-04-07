/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:38:24 by ejones            #+#    #+#             */
/*   Updated: 2026/04/07 18:29:25 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long	res;
	int		i;

	res = 0;
	i = 1;
	if (!nptr)
		return (0);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if ((*nptr == '+' || *nptr == '-'))
	{
		if (*nptr == '-')
			i *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (res < -2147483648 || res > 2147483647)
			return (-1);
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	if (res < -2147483648 || res > 2147483647)
		return (-1);
	return (res * i);
}
