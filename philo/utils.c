/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:55 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/26 23:34:23 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

long	gettime(int time_code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		print_error("Wrong input to gettime:"
			"use <MILLISECOND> <MICROSECOND> <SECONDS>");
	return (1);
}

void	ft_usleep(long usec, t_table *table)
{
	long	start;
	long	passed_time;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (mission_complete(table))
			break ;
		passed_time = gettime(MICROSECOND) - start;
		rem = usec - passed_time;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (gettime(MICROSECOND) - start < usec)
				;
	}
}

void	clear_process(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		function_mutex(&philo->philo_mutex, DESTROY);
		i++;
	}
	function_mutex(&table->datamutex, DESTROY);
	function_mutex(&table->print_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

int	print_error(const char *error)
{
	printf(RED"Error : "W"%s\n", error);
	return (0);
}
