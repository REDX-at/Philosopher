/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:47 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/31 16:46:03 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_left_fork,
	TAKE_right_fork,
	DIED,
}			t_philo_status;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

# define RESET    "\033[0m"
# define RED	"\033[1;31m"
# define G      "\033[1;32m"
# define Y      "\033[1;33m"
# define B      "\033[1;34m"
# define M      "\033[1;35m"
# define C      "\033[1;36m"
# define W      "\033[1;37m"

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx		fork;
	int			fork_id;
}				t_fork;

typedef struct s_philo
{
	int				id;
	bool			full;
	long			count_meals;
	long			last_meal;
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mtx			philo_mutex;
	t_table			*table;
}				t_philo;

struct	s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meal_limit_number;
	long				philo_nbr;
	long				start_simulation;
	bool				end_simulation;
	bool				thread_ready;
	long				thread_exe_nbr;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				datamutex;
	t_mtx				print_mutex;
};

int		function_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
int		function_mutex(t_mtx *mutex, t_opcode opcode);
void	*pro_malloc(size_t bytes);
int		parse_args(t_table *table, char **av);
int		init_data(t_table *table);
void	dinner_start(t_table *table);
void	set_bool(t_mtx *mutex, bool *dest, bool result);
bool	get_bool(t_mtx *mutex, bool *result);
long	get_long(t_mtx *mutex, long *result);
void	set_long(t_mtx *mutex, long *dest, long result);
bool	mission_complete(t_table *table);
time_t	gettime(int time_code);
void	ft_usleep(long usec, t_table *table);
void	clear_process(t_table *table);
int		print_error(const char *error);
void	print_state(t_philo_status status, t_philo *philo);
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *result);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	thinking(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);
void	*watch_dinner(void *data);

#endif
