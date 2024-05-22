/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:05:47 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/22 12:32:07 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

void	print_stat(t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf(W"%ld %ld %s\n", get_time() - philo->start, philo->philo_id, str);
	sem_post(philo->print);
}

void	ft_usleep(int duration)
{
	long	time_start;

	time_start = get_time();
	while (get_time() - time_start < duration)
	{
		usleep(100);
	}
}

int	init_sema(t_philo *philo)
{
	sem_unlink("print");
	sem_unlink("forks");
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->nb_forks);
	if (philo->print <= 0 || philo->forks <= 0)
	{
		print_err(RED"Error: "W"Failed to create semaphore\n");
		return (1);
	}
	return (0);
}

t_philo	*init_table(int argc, char **argv)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		exit(1);
	philo->id = malloc(sizeof(int) * ft_atoi(argv[1]));
	if (!philo->id)
		exit(1);
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_must_eat = ft_atoi(argv[5]);
	else
		philo->nb_must_eat = -1;
	if (philo->nb_must_eat == 0)
		exit(1);
	philo->counter = 0;
	philo->stop = 0;
	philo->died = 0;
	philo->nb_forks = philo->nb_philo;
	if (init_sema(philo))
		exit(1);
	return (philo);
}
