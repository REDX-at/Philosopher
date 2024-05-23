/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:12:42 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/22 12:23:09 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (get_time() - philo->last_eat > philo->time_to_die)
		{
			sem_wait(philo->print);
			printf("%ld %ld died\n", get_time() - philo->start, \
				philo->philo_id);
			exit (1);
		}
		if (philo->nb_must_eat != -1 && philo->counter >= philo->nb_must_eat)
			exit (0);
	}
	return (NULL);
}

void	philo_state(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, \
			NULL, &check_death, philo))
		print_err("Error: Failed to create the thread");
	while (1)
	{
		sem_wait(philo->forks);
		print_stat(philo, "has taken a fork");
		sem_wait(philo->forks);
		print_stat(philo, "has taken a fork");
		print_stat(philo, "is eating");
		ft_usleep(philo->time_to_eat);
		philo->last_eat = get_time();
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->counter += 1;
		print_stat(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		print_stat(philo, "is thinking");
	}
	if (pthread_join(philo->check_monitor, NULL))
		print_err("Error: Failed to join the thread");
}

void	exit_philo(t_philo *tmp)
{
	int		i;
	int		status;

	i = -1;
	while (++i < tmp->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->nb_philo)
				kill(tmp->id[i], SIGKILL);
			break ;
		}
	}
	sem_close(tmp->print);
	sem_close(tmp->forks);
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	free(tmp->id);
	free(tmp);
}

int	init_process(t_philo *philo)
{
	int	i;

	i = -1;
	philo->start = get_time();
	while (++i < philo->nb_philo)
	{
		philo->id[i] = fork();
		if (philo->id[i] == -1)
			print_err("Error: fork mistake");
		if (philo->id[i] == 0)
		{
			philo->philo_id = i + 1;
			philo->last_eat = get_time();
			philo_state(philo);
		}
	}
	exit_philo(philo);
	return (0);
}
