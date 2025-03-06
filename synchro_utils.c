/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:59:32 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 17:25:30 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads_ready(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_treads_ready))
		;
}

bool	all_threads_running(pthread_mutex_t *mutex,
	long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	de_sync_philos(t_philo *philo)
{
	if (philo->table->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
		else
		{
			if (philo->id % 2)
				think(philo, false);
		}
	}
}
