/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:14:06 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 17:19:51 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status)
		printf(B"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
	else if (TAKE_SECOND_FORK == status)
		printf(B"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status)
		printf(B"%-6ld"RST" %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status)
		printf(B"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status)
		printf(B"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(R"%-6ld"RST" %d died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILISECOND) - philo->table->start_time;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_lock, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(R"%-6ld"RST" %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}
