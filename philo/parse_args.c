/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:45 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/26 23:09:10 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;
	int			retu;

	(1) && (retu = 1, len = -1);
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		retu = print_error("Feed me only positive results");
	while (str[++len])
	{
		if (!is_digit(str[len]))
			retu = print_error("The input is not a correct digit");
	}
	len = 0;
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		retu = print_error("The result is too big, INT_MAX is the limit");
	if (!retu)
		return (NULL);
	return (number);
}

static long	ft_atol(const char *str, int *flag)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (!str)
	{
		*flag = 0;
		return (0);
	}
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		*flag = print_error("INT_MAX is the limit, not the sky");
	return (num);
}

int	parse_args(t_table *table, char **av)
{
	int	flag;

	flag = 1;
	table->philo_nbr = ft_atol(av[1], &flag);
	table->time_to_die = ft_atol(av[2], &flag) * 1e3;
	table->time_to_eat = ft_atol(av[3], &flag) * 1e3;
	table->time_to_sleep = ft_atol(av[4], &flag) * 1e3;
	if (av[5])
		table->meal_limit_number = ft_atol(av[5], &flag);
	else
		table->meal_limit_number = -1;
	if (flag)
		return (1);
	return (0);
}
