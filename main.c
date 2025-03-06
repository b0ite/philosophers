/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:15:09 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 17:26:02 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		err_exit("Error: Wrong input\n"
			G"Usage: ./philo nb_philo ttd tte tts [nb_must_eat]"RST);
	}
	parse_input(&table, av);
	data_init(&table);
	lets_eat(&table);
	clean(&table);
	return (0);
}
