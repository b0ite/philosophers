/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:11:15 by igilbert          #+#    #+#             */
/*   Updated: 2025/03/06 16:04:51 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		err_exit("Error: Malloc failed");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opc)
{
	if (status == 0)
		return ;
	else if (EINVAL == status && (opc == LOCK || opc == UNLOCK
			|| opc == DESTROY))
		err_exit("the value specified by mutex is invalid\n");
	else if (EINVAL == status && (opc == INIT))
		err_exit("the value specified by attr is invalid\n");
	else if (EDEADLK == status)
		err_exit("A dead lock would occur"
			" if the thread blocked waiting for mutex\n");
	else if (EPERM == status)
		err_exit("the current thread does not hold a lock on mutex\n");
	else if (ENOMEM == status)
		err_exit("The process cannot allocate enough memory to create"
			" another mutex\n");
	else if (EBUSY == status)
		err_exit("Mutex is locked\n");
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		err_exit("Error: Wrong mutex opcode");
}

static void	thread_error(int status, t_opcode opc)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		err_exit("Insufficient resources to create another thread\n");
	else if (EPERM == status)
		err_exit("The caller does not have appropriate perimission\n");
	else if (EINVAL == status && CREATE == opc)
		err_exit("The value specified by attr is invalid\n");
	else if (EINVAL == status && (JOIN == opc || DETACH == opc))
		err_exit("The thread is not joinable\n");
	else if (ESRCH == status)
		err_exit("No thread could be found corresponding to that specified"
			" by the given thread ID, thread\n");
	else if (EDEADLK == status)
		err_exit("A deadlock was detected or the value of thread specifies"
			" the calling thread\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*func)(void *),
	void *arg, t_opcode opc)
{
	if (opc == CREATE)
		thread_error(pthread_create(thread, NULL, func, arg), opc);
	else if (opc == JOIN)
		thread_error(pthread_join(*thread, NULL), opc);
	else if (opc == DETACH)
		thread_error(pthread_detach(*thread), opc);
	else
		err_exit("wrong opc for the thread handle"
			" use <CREATE JOIN DETACH>\n");
}
