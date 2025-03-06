/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:17:30 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 17:26:27 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
	{
		return (true);
	}
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->nb_philo))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->nb_philo)
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_sim, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
