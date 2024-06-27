/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:20:21 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/27 14:19:23 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Free memory
void	free_memory(t_data *data)
{
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
}

// Unlink semaphore
void	sem_unlink_all(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_DEATH_DECLARED);
	sem_unlink(SEM_DEATH_PRINT);
}

// Close semaphore and clean memory
void	sem_close_all(t_data *data)
{
	int	error;

	error = 0;
	if (sem_close(data->forks) == -1)
		error = 1;
	if (sem_close(data->dead_check) == -1)
		error = 1;
	if (sem_close(data->print) == -1)
		error = 1;
	if (sem_close(data->lastmeal_check) == -1)
		error = 1;
	if (sem_close(data->sem_stop) == -1)
		error = 1;
	if (sem_close(data->death_declared) == -1)
		error = 1;
	if (sem_close(data->death_print) == -1)
		error = 1;
	if (error)
		exit(EXIT_FAILURE);
}
