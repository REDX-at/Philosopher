/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:03:44 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/21 18:54:56 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Header
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// Includes
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>

// Colors
# define RESET    "\033[0m"
# define RED	"\033[1;31m"
# define G      "\033[1;32m"
# define Y      "\033[1;33m"
# define B      "\033[1;34m"
# define M      "\033[1;35m"
# define C      "\033[1;36m"
# define W      "\033[1;37m"

// struct for philos
typedef struct s_philo
{
	long			nb_must_eat;
	long			nb_forks;
	long			philo_id;
	sem_t			*print;
	sem_t			*forks;
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				*id;
	long			counter;
	long			last_eat;
	long			stop;
	long			died;
	long			start;
	pthread_t		check_monitor;
}	t_philo;

// Functions
int		parse_args(char **av);
int		print_err(char *str);
int		ft_strlen(char *str);
void	print_stat(t_philo *philo, char *str);
long	get_time(void);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
t_philo	*init_table(int argc, char **argv);
int		init_sema(t_philo *philo);
void	print_stat(t_philo *philo, char *str);
int		init_process(t_philo *philo);
void	exit_philo(t_philo *tmp);
void	philo_state(t_philo *philo);
void	*check_death(void *args);
void	ft_usleep(int duration);

#endif