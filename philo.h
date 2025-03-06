/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:20:25 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 17:27:03 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

#define R "\e[1;31m"
#define G "\e[1;32m"
#define Y "\e[1;33m"
#define B "\e[1;34m"
#define P "\e[1;35m"
#define C "\e[1;36m"
#define W "\e[1;37m"
#define RST "\e[0m"

#define DEBUG_MODE 0

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND
}	t_time_code;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	bool			full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	int				nb_meals;
	long			last_meal;
	pthread_t		thread_id;
	t_table			*table;
	pthread_mutex_t	philo_mutex;
}	t_philo;

struct s_table
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			nb_philo;
	long			limit_meals;
	bool			end_sim;
	bool			all_treads_ready;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_lock;
	pthread_t		monitor;
	long			threads_running_nbr;
};

void		err_exit(char *str);
void		parse_input(t_table *table, char **av);
void		data_init(t_table *table);
void		lets_eat(t_table *table);
void		safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void		*safe_malloc(size_t bytes);
void		safe_thread_handle(pthread_t *thread, void *(*func)(void *),
				void *arg, t_opcode opc);
bool		simulation_finished(t_table *table);
void		set_long(pthread_mutex_t *mutex, long *dest, long value);
long		get_long(pthread_mutex_t *mutex, long *value);
bool		get_bool(pthread_mutex_t *mutex, bool *value);
void		set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void		wait_all_threads_ready(t_table *table);
void		precise_usleep(long usec, t_table *table);
void		write_status(t_philo_status status, t_philo *philo, bool debug);
void		clean(t_table *table);
long		get_time(t_time_code time_code);
void		*monitor_dinner(void *data);
bool		all_threads_running(pthread_mutex_t *mutex,
				long *threads, long philo_nbr);
void		wait_all_threads_ready(t_table *table);
void		increase_long(pthread_mutex_t *mutex, long *dest);
void		think(t_philo *philo, bool pre_simulation);
void		de_sync_philos(t_philo *philo);