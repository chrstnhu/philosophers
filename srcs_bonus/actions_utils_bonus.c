/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:23:40 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/10 19:48:22 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Philo eat, update last_meal and ate number 
void	philo_eating(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	print_status(data, philo->philo, "has taken a fork", 0);
	print_status(data, philo->philo, "has taken a fork", 0);
	sem_wait(data->lastmeal_check);
	philo->last_meal = get_time();
	sem_post(data->lastmeal_check);
	print_status(data, philo->philo, "is eating", 0);
	ft_usleep(data, data->time_to_eat);
	sem_wait(data->meal_check);
	philo->philo_ate++;
	sem_post(data->meal_check);
	sem_post(data->forks);
	sem_post(data->forks);
}

// Print the status of the philo
void	print_status(t_data *data, int philo, const char *status, int dead)
{
	long long	current_time;

	current_time = get_time();
	sem_wait(data->print);
	if (!philo_status(data) || dead == 1)
	{
		printf("%lld %d ", current_time - data->start_time, philo + 1);
		printf("%s\n", status);
	}
	sem_post(data->print);
}

// Usleep time (eat, sleep)
void	ft_usleep(t_data *data, long long time)
{
	long long	start;

	start = get_time();
	while (!philo_status(data) && (get_time() - start) < time)
		usleep(1000);
}

// Convert seconds and microseconds to millisecondes
long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		printf("%sError function : gettimeofday()%s\n", RED, DEFAULT);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
