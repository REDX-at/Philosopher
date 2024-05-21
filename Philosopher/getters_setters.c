/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:34 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/31 16:46:03 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx	*mutex, bool *dest, bool result)
{
	function_mutex(mutex, LOCK);
	*dest = result;
	function_mutex(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *result)
{
	bool	ret;

	function_mutex(mutex, LOCK);
	ret = *result;
	function_mutex(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *result)
{
	long	ret;

	function_mutex(mutex, LOCK);
	ret = *result;
	function_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long result)
{
	function_mutex(mutex, LOCK);
	*dest = result;
	function_mutex(mutex, UNLOCK);
}

bool	mission_complete(t_table *table)
{
	bool	ret;

	function_mutex(&table->datamutex, LOCK);
	ret = table->end_simulation;
	function_mutex(&table->datamutex, UNLOCK);
	return (ret);
}
