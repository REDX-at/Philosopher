/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:23:39 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/22 23:01:07 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (5 == ac || 6 == ac)
	{
		if (!parse_args(&table, av))
			return (0);
		if (!init_data(&table))
		{
			clear_process(&table);
			return (0);
		}
		dinner_start(&table);
		clear_process(&table);
	}
	else
	{
		if (!print_error("Wrong input"RESET))
			return (0);
	}
	return (1);
}
