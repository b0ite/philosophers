/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:15:05 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 16:55:34 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_exit(char *str)
{
	printf(R"%s\n"RST, str);
	exit(EXIT_FAILURE);
}

long	get_time(t_time_code time_code)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL))
		err_exit("Error : gettimeofday fafiled");
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (time_code == SECOND)
		return (time / 1000);
	else if (time_code == MILISECOND)
		return (time);
	else if (time_code == MICROSECOND)
		return (time * 1000);
	else
		err_exit("Error : wrong input to gettime");
	return (1337);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start_time;
	long	elapsed;
	long	rem;

	start_time = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start_time < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start_time;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (get_time(MICROSECOND) - start_time < usec)
				;
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->nb_philo)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->table_mutex, DESTROY);
	safe_mutex_handle(&table->write_lock, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	increase_long(pthread_mutex_t *mutex, long *dest)
{
	safe_mutex_handle(mutex, LOCK);
	(*dest)++;
	safe_mutex_handle(mutex, UNLOCK);
}
