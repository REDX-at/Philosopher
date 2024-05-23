/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:57 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/23 10:31:44 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

void	print_state(t_philo_status status, t_philo *philo)
{
	long	passed_time;

	passed_time = gettime(MILLISECOND) - philo->table->start_simulation;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	function_mutex(&philo->table->print_mutex, LOCK);
	if ((TAKE_left_fork == status || TAKE_right_fork == status)
		&& !mission_complete(philo->table))
		printf(W"%-6ld %d has taken a fork\n", passed_time, philo->id);
	else if (EATING == status && !mission_complete(philo->table))
		printf(W"%-6ld %d is eating\n", passed_time, philo->id);
	else if (SLEEPING == status && !mission_complete(philo->table))
		printf(W"%-6ld %d is sleeping\n", passed_time, philo->id);
	else if (THINKING == status && !mission_complete(philo->table))
		printf(W"%-6ld %d is thinking\n", passed_time, philo->id);
	else if (DIED == status)
		printf(W"%-6ld %d died\n", passed_time, philo->id);
	function_mutex(&philo->table->print_mutex, UNLOCK);
}
