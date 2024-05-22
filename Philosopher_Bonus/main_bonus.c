/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:42:47 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/22 18:35:20 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc < 5 | argc > 6 | parse_args(argv))
		print_err(RED"Error: "W"Invalid arguments\n");
	philo = init_table(argc, argv);
	if (!philo)
	{
		print_err(RED"Error: "W"Failed to init table\n");
		return (1);
	}
	init_process(philo);
	return (0);
}
