/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:41 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/31 16:50:11 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static bool	is_dead(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	time_passed = gettime(MILLISECOND)
		- get_long(&philo->philo_mutex, &philo->last_meal);
	time_to_die = philo->table->time_to_die / 1e3;
	if (time_passed > time_to_die)
		return (true);
	return (false);
}

void	*watch_dinner(void *data)
{
	int			i;
	t_table		*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->datamutex,
			&table->thread_exe_nbr, table->philo_nbr))
		;
	while (!mission_complete(table))
	{
		i = 0;
		while (i < table->philo_nbr && !mission_complete(table))
		{
			if (is_dead(table->philos + i))
			{
				set_bool(&table->datamutex, &table->end_simulation, true);
				print_state(DIED, table->philos + i);
			}
			i++;
		}
	}
	return (NULL);
}
