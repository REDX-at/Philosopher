/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:49 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/12 14:35:33 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*pro_malloc(size_t bytes)
{
	void	*ret;
	int		retu;

	retu = 1;
	ret = malloc(bytes);
	if (NULL == ret)
	{
		retu = print_error("Error with the malloc");
		return (NULL);
	}
	return (ret);
}

int	function_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == opcode)
		pthread_mutex_unlock(mutex);
	else if (INIT == opcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == opcode)
		pthread_mutex_destroy(mutex);
	else
		return (0);
	return (1);
}

int	function_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		pthread_create(thread, NULL, foo, data);
	else if (JOIN == opcode)
		pthread_join(*thread, NULL);
	else if (DETACH == opcode)
		pthread_detach(*thread);
	else
		return (0);
	return (1);
}
