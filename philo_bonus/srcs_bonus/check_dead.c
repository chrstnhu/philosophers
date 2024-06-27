/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:20:13 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/27 18:42:19 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Change philo to dead and check if already print
int	died_and_check_print(t_data *data)
{
	sem_wait(data->dead_check);
	data->philo_dead = true;
	sem_post(data->dead_check);
	if (!is_printed(data))
	{
		sem_wait(data->death_print);
		data->death_printed = true;
		sem_post(data->death_print);
		return (1);
	}
	return (0);
}

// Check if philo dead with the lastmeal
void	*check_dead(void *philosopher)
{
	t_philo		*philo;
	t_data		*data;
	long long	elapsed_time;

	philo = (t_philo *)philosopher;
	data = philo->data;
	while (!is_dead(data))
	{
		sem_wait(data->lastmeal_check);
		elapsed_time = get_time() - philo->last_meal;
		sem_post(data->lastmeal_check);
		sem_wait(data->death_declared);
		if (elapsed_time > data->time_to_die)
		{
			if (!is_dead(data))
			{
				if (died_and_check_print(data) == 1)
					return (NULL);
			}
		}
		sem_post(data->death_declared);
		usleep(1000);
	}
	return (NULL);
}

// Check before usleep if time(sleep, think) exceed the time to die
int	is_time_exceed(t_philo *philo, long long time, int status)
{
	long long	current_time;
	t_data		*data;

	data = philo->data;
	sem_wait(data->lastmeal_check);
	current_time = time - philo->last_meal + data->time_to_sleep;
	sem_post(data->lastmeal_check);
	if (status == 1 && current_time > data->time_to_die)
		return (1);
	if (status == 2 && data->time_to_think != -1 && data->nb_philo % 2 == 0
		&& data->time_to_eat * 2 < data->time_to_die)
		return (0);
	else if (status == 2 && data->time_to_think != -1)
	{
		sem_wait(data->lastmeal_check);
		current_time = time - philo->last_meal + data->time_to_think;
		sem_post(data->lastmeal_check);
		if ((current_time > data->time_to_die + 0.5 * data->nb_philo))
			return (1);
	}
	return (0);
}

// Verify if time exceed, dead already print or is dead
int	verify_dead(t_philo *philo, long long curr_time, int status)
{
	t_data	*data;

	data = philo->data;
	if (status == 1)
	{
		if (is_time_exceed(philo, curr_time, 1)
			|| is_printed(data) || is_dead(data))
			return (1);
	}
	if (status == 2)
	{
		if (is_time_exceed(philo, curr_time, 2)
			|| is_printed(data) || is_dead(data))
			return (1);
	}
	return (0);
}

// Return if philo live or dead
int	is_dead(t_data *data)
{
	int	philo_status;

	sem_wait(data->dead_check);
	philo_status = data->philo_dead;
	sem_post(data->dead_check);
	return (philo_status);
}
