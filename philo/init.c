/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:36 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/31 16:46:03 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	distribute_forks(t_philo *philo, t_fork *forks,
		int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->right_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[philo_position];
		philo->right_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->count_meals = 0;
		if (!function_mutex(&philo->philo_mutex, INIT))
			return (0);
		philo->table = table;
		distribute_forks(philo, table->forks, i);
	}
	return (1);
}

int	init_data(t_table *table)
{
	int		i;

	i = -1;
	table->end_simulation = false;
	table->thread_ready = false;
	table->thread_exe_nbr = 0;
	table->philos = pro_malloc(table->philo_nbr * sizeof(t_philo));
	table->forks = pro_malloc(table->philo_nbr * sizeof(t_fork));
	if (!table->philos || !table->forks)
		return (0);
	if (!function_mutex(&table->print_mutex, INIT))
		return (0);
	if (!function_mutex(&table->datamutex, INIT))
		return (0);
	while (++i < table->philo_nbr)
	{
		if (!function_mutex(&table->forks[i].fork, INIT))
			return (0);
		table->forks[i].fork_id = i;
	}
	if (!philo_init(table))
		return (0);
	return (1);
}
