/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:20:21 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/05 14:10:13 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_no_dead(t_data *data)
{
	int	philo_dead;

	pthread_mutex_lock(&(data->dead_check));
	philo_dead = data->philo_dead;
	pthread_mutex_unlock(&(data->dead_check));
	return (philo_dead);
}

int	number_of_ate(t_data *data, int philo_id)
{
	int	philo_ate;

	pthread_mutex_lock(&data->meal_check);
	philo_ate = data->philo[philo_id].philo_ate;
	pthread_mutex_unlock(&data->meal_check);
	return (philo_ate);
}

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
