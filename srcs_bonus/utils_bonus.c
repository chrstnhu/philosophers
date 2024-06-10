/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:20:21 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/10 19:48:31 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Check if all philo ate the number of meals
int	philo_all_ate(t_data *data)
{
	sem_wait(data->all_ate_check);
	if (data->all_ate)
	{
		sem_post(data->all_ate_check);
		return (1);
	}
	sem_post(data->all_ate_check);
	return (0);
}

// Return if philo live or dead
int	philo_status(t_data *data)
{
	int	philo_status;

	sem_wait(data->dead_check);
	philo_status = data->philo_dead;
	sem_post(data->dead_check);
	return (philo_status);
}

// Return the number of meals
int	number_of_meals(t_data *data, int philo_id)
{
	int	philo_ate;

	sem_wait(data->meal_check);
	philo_ate = data->philo[philo_id].philo_ate;
	sem_post(data->meal_check);
	return (philo_ate);
}

// Check overflow and negative number
int	check_number(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) > 0)
		return (0);
	return (0);
}

// Convert string into number
int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result);
}
