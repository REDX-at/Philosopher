/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:31 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/31 16:48:22 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		print_state(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo->table);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->datamutex,
		&philo->table->thread_exe_nbr);
	print_state(TAKE_left_fork, philo);
	while (!mission_complete(philo->table))
		ft_usleep(200, philo->table);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	function_mutex(&philo->left_fork->fork, LOCK);
	print_state(TAKE_left_fork, philo);
	function_mutex(&philo->right_fork->fork, LOCK);
	print_state(TAKE_right_fork, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	philo->count_meals++;
	print_state(EATING, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meal_limit_number > 0
		&& philo->count_meals == philo->table->meal_limit_number)
		set_bool(&philo->philo_mutex, &philo->full, true);
	function_mutex(&philo->left_fork->fork, UNLOCK);
	function_mutex(&philo->right_fork->fork, UNLOCK);
}

static void	*dinner_simulation(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal,
		gettime(MILLISECOND));
	increase_long(&philo->table->datamutex,
		&philo->table->thread_exe_nbr);
	de_synchronize_philos(philo);
	while (!mission_complete(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		print_state(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int			i;

	i = -1;
	if (0 == table->meal_limit_number)
		return ;
	else if (1 == table->philo_nbr)
		function_thread(&table->philos[0].thread_id, one_philo,
			&table->philos[0], CREATE);
	else
		while (++i < table->philo_nbr)
			function_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	function_thread(&table->monitor, watch_dinner, table, CREATE);
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->datamutex, &table->thread_ready, true);
	i = 0;
	while (i < table->philo_nbr)
	{
		function_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&table->datamutex, &table->end_simulation, true);
	function_thread(&table->monitor, NULL, NULL, JOIN);
}
