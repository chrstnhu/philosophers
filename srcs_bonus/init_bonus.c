/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:20:15 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/10 19:48:26 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Destroy thread and mutex
void	thread_wait_destroy(t_data *data, t_philo *philo)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		if (pthread_join(philo[i].threads, NULL) != 0)
			return ;
	}
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->meal_check);
	sem_close(data->dead_check);
	sem_close(data->lastmeal_check);
	sem_close(data->all_ate_check);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_ALL_ATE);
}

// Create semaphore
static int	create_semaphore(sem_t **sem, char *name, int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value);
	return (*sem == SEM_FAILED);
}

// Initialize semaphore
int	init_semaphore(t_data *data)
{
	if (create_semaphore(&data->forks, SEM_FORKS, data->nb_philo))
		return (1);
	if (create_semaphore(&data->dead_check, SEM_DEAD, 1))
		return (1);
	if (create_semaphore(&data->print, SEM_PRINT, 1))
		return (1);
	if (create_semaphore(&data->lastmeal_check, SEM_LAST_MEAL, 1))
		return (1);
	if (create_semaphore(&data->meal_check, SEM_MEAL, 1))
		return (1);
	if (create_semaphore(&data->all_ate_check, SEM_ALL_ATE, 1))
		return (1);
	return (0);
}

// Initialize philo
int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].philo = i;
		data->philo[i].philo_ate = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].data = data;
	}
	return (0);
}

// Initialize structure
int	initialize(t_data *data, char **argv)
{
	data->all_ate = false;
	data->philo_dead = false;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_meals = -1;
	if (argv[5])
		data->nb_meals = ft_atoi(argv[5]);
	if (argv[5] < 0)
		data->nb_meals = -1;
	if (data->nb_philo > 250 || data->nb_philo < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	init_philo(data);
	if (init_semaphore(data))
		return (1);
	return (0);
}
