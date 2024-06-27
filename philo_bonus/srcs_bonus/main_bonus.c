/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:20:19 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/27 19:02:04 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5)
	{
		if ((check_number(argc, argv) == 1))
		{
			printf("%sError init philo%s", RED, DEFAULT);
			return (1);
		}
		if (initialize(&data, argv) == 1 || init_process(&data) == 1)
		{
			printf("%sError init philo%s", RED, DEFAULT);
			free_memory(&data);
			return (1);
		}
		free_memory(&data);
	}
	else
	{
		printf("%sPlease enter 5 args :", RED);
		printf("./philo number_of_philosopher time_to_die");
		printf(" time_to_eat time_to_sleep%s\n", DEFAULT);
		return (1);
	}
	return (0);
}
