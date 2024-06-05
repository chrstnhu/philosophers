/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:20:13 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/05 14:14:29 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_one_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->nb_philo == 1)
	{
		print_status(data, philo->philo, "has taken a fork", 0);
		return (1);
	}
	return (0);
}

static void	wait_for_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_mutex);
		if (data->start_flag)
		{
			pthread_mutex_unlock(&data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->start_mutex);
		usleep(100);
	}
}

void	*action(void *philosopher)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	wait_for_start(data);
	if (is_one_philo(philo) == 1)
		return (NULL);
	if (philo->philo % 2 == 0)
		usleep(500 * data->time_to_eat);
	while (!philo_no_dead(data))
	{
		philo_eating(philo, data);
		pthread_mutex_lock(&data->eat_check);
		if (data->all_ate)
		{
			pthread_mutex_unlock(&data->eat_check);
			break ;
		}
		pthread_mutex_unlock(&data->eat_check);
		print_status(data, philo->philo, "is sleeping", 0);
		ft_usleep(data, data->time_to_sleep);
		print_status(data, philo->philo, "is thinking", 0);
	}
	return (0);
}

/*
static void	check_philo_ate(t_data *data)
{
	int i;

	i = 0;
    while (data->nb_eat > 0 && i < data->nb_philo
		&& number_of_ate(data, i) >= data->nb_eat)
		i++;
	if (data->nb_philo == i)
	{
		pthread_mutex_lock(&data->eat_check);
	    data->all_ate = true;
		pthread_mutex_unlock(&data->eat_check);
		printf("All philosophers have eaten enough.\n");
	}
}
*/

void	check_dead(t_data *data, t_philo *philo)
{
	int			i;
	long long	elapsed_time;

	while (!(data->all_ate))
	{
		i = -1;
		while (!philo_no_dead(data) && ++i < data->nb_philo)
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
		}
		i = 0;
		while (data->nb_eat > 0 && i < data->nb_philo
			&& number_of_ate(data, i) >= data->nb_eat)
			i++;
		if (data->nb_philo == i)
		{
			pthread_mutex_lock(&data->eat_check);
			data->all_ate = true;
			pthread_mutex_unlock(&data->eat_check);
		}
	}
}

int	init_thread(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = data->philo;
	data->start_time = get_time();
	pthread_mutex_lock(&data->start_mutex);
	while (i < data->nb_philo)
	{
		if ((pthread_create(&(philo[i].threads), NULL, action, &philo[i])) != 0)
			return (1);
		pthread_mutex_lock(&data->lastmeal_check);
		philo[i].last_meal = get_time();
		pthread_mutex_unlock(&data->lastmeal_check);
		i++;
	}
	data->start_flag = 1;
	pthread_mutex_unlock(&data->start_mutex);
	check_dead(data, data->philo);
	thread_wait_destroy(data, philo);
	return (0);
}
