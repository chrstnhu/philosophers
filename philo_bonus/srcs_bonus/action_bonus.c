/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:20:13 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/27 18:16:06 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Cleanup data and exit if philo dead
void	exit_action(t_data *data, t_philo *philo)
{
	if (is_dead(data))
	{
		usleep(100);
		print_status(data, philo->philo, "died", 1);
		sem_post(data->print);
		sem_post(data->death_declared);
		sem_post(data->sem_stop);
		sem_close_all(data);
		free_memory(data);
		exit(EXIT_FAILURE);
	}
}

// Action of philo
void	*action(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	philo->last_meal = get_time();
	if (pthread_create(&philo->threads, NULL, check_dead, philo) != 0)
		exit(EXIT_FAILURE);
	if (philo->philo % 2)
		usleep(500 * data->time_to_eat);
	while (!is_dead(data) && !is_printed(data))
	{
		philo_eating(philo, data);
		if (data->nb_philo == 1 || verify_dead(philo, get_time(), 1))
			break ;
		print_status(data, philo->philo, "is sleeping", 0);
		ft_usleep(data, data->time_to_sleep);
		if (verify_dead(philo, get_time(), 2))
			break ;
		print_status(data, philo->philo, "is thinking", 0);
		if (data->nb_philo % 2 == 1 && data->time_to_think != -1)
			usleep(1000 * data->time_to_eat);
	}
	pthread_join(philo->threads, NULL);
	exit_action(data, philo);
	exit(EXIT_SUCCESS);
}

// Wait child process and clean semaphore and memory
void	wait_and_close(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->nb_philo)
				kill(data->philo[i].pid, SIGKILL);
			break ;
		}
		i++;
	}
	sem_post(data->sem_stop);
	sem_close_all(data);
	free_memory(data);
}

// Initialize child process, one per philo
int	init_process(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = data->philo;
	data->start_time = get_time();
	sem_wait(data->sem_stop);
	while (++i < data->nb_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			return (1);
		if (philo[i].pid == 0)
			action(&(philo[i]));
		usleep(100);
	}
	wait_and_close(data);
	return (0);
}
