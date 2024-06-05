/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:20:13 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/05 17:09:35 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Check if all philosopher have ate the number of times required
static void	check_philo_ate(t_data *data)
{
	int	i;

	i = 0;
	while (data->nb_meals > 0 && i < data->nb_philo
		&& number_of_meals(data, i) >= data->nb_meals)
		i++;
	if (data->nb_philo == i)
	{
		pthread_mutex_lock(&data->all_ate_check);
		data->all_ate = true;
		pthread_mutex_unlock(&data->all_ate_check);
	}
}

// Check if philo dead
void	check_dead(t_data *data, t_philo *philo)
{
	int			i;
	long long	elapsed_time;

	while ((philo_all_ate(data) != 1) && !philo_status(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			usleep(100);
			pthread_mutex_lock(&data->lastmeal_check);
			elapsed_time = get_time() - philo[i].last_meal;
			pthread_mutex_unlock(&data->lastmeal_check);
			if (elapsed_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->dead_check);
				data->philo_dead = true;
				pthread_mutex_unlock(&data->dead_check);
				print_status(data, philo[i].philo, "died", 1);
				return ;
			}
			i++;
		}
		check_philo_ate(data);
	}
}

// Action of philosopher : eat, sleep, think
void	*action(void *philosopher)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	if (data->nb_philo == 1)
	{
		print_status(data, philo->philo, "has taken a fork", 0);
		return (0);
	}
	if (philo->philo % 2 == 0)
		usleep(500 * data->time_to_eat);
	while (!philo_status(data))
	{
		philo_eating(philo, data);
		if (philo_all_ate(data) == 1)
			break ;
		print_status(data, philo->philo, "is sleeping", 0);
		ft_usleep(data, data->time_to_sleep);
		print_status(data, philo->philo, "is thinking", 0);
		if (data->nb_philo % 2 == 1 && data->time_to_eat >= data->time_to_sleep)
			usleep(1000 * data->time_to_eat);
	}
	return (0);
}

// Initialize thread
int	init_thread(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = data->philo;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		if ((pthread_create(&(philo[i].threads), NULL, action, &philo[i])) != 0)
			return (1);
		pthread_mutex_lock(&data->lastmeal_check);
		philo[i].last_meal = get_time();
		pthread_mutex_unlock(&data->lastmeal_check);
		i++;
	}
	check_dead(data, data->philo);
	thread_wait_destroy(data, philo);
	return (0);
}
