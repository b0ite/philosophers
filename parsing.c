/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:45:19 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 17:25:36 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_atol_str(const char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str > '0' || *str < '9')
		{
			len++;
			if (len > 10)
			{
				err_exit("Error: Number is too big (INT_MAX is the limit)");
			}
		}
		str++;
	}
}

static long	ft_atol(const char *str)
{
	long	nb;

	nb = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			err_exit("Error: Only positive numbers are allowed");
		str++;
	}
	if (*str < '0' || *str > '9')
		err_exit("Error: Only numbers are allowed");
	check_atol_str(&*str);
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (nb > INT_MAX)
		err_exit("Error: Number is too big (INT_MAX is the limit)");
	return (nb);
}

void	parse_input(t_table *table, char **av)
{
	table->nb_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		err_exit("Error: Time must be at least 60ms");
	if (av[5])
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
}
