/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:09:22 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 17:25:40 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	nb_philo;

	nb_philo = philo->table->nb_philo;
	philo->first_fork = forks + pos;
	philo->second_fork = forks + ((pos + 1) % nb_philo);
	if (philo->id % 2 == 0)
	{
		philo->first_fork = forks + ((pos + 1) % nb_philo);
		philo->second_fork = forks + pos;
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nb_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->nb_meals = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
		safe_mutex_handle(&philo->philo_mutex, INIT);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->all_treads_ready = false;
	table->end_sim = false;
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_lock, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->nb_philo);
	table->philos = safe_malloc(sizeof(t_philo) * table->nb_philo);
	table->threads_running_nbr = 0;
	while (++i < table->nb_philo)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].id = i;
	}
	philo_init(table);
}
