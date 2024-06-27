/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:23:40 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/13 19:01:21 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Philo eat, update last_meal and ate number 
void	philo_eating(t_philo *philo, t_data *data)
{
	if (data->nb_philo == 1)
	{
		pthread_mutex_lock(&(data->print));
		printf("%lld 1 ", data->start_time - data->start_time);
		printf("has taken a fork\n");
		pthread_mutex_unlock(&(data->print));
		return ;
	}
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_status(data, philo->philo, "has taken a fork", 0);
	print_status(data, philo->philo, "has taken a fork", 0);
	pthread_mutex_lock(&data->lastmeal_check);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->lastmeal_check);
	print_status(data, philo->philo, "is eating", 0);
	ft_usleep(data, data->time_to_eat);
	pthread_mutex_lock(&data->meal_check);
	philo->philo_ate++;
	pthread_mutex_unlock(&data->meal_check);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

// Return if philo live or dead
int	is_philo_dead(t_data *data)
{
	int	philo_status;

	pthread_mutex_lock(&(data->dead_check));
	philo_status = data->philo_dead;
	pthread_mutex_unlock(&(data->dead_check));
	return (philo_status);
}

// Print the status of the philo
void	print_status(t_data *data, int philo, const char *status, int dead)
{
	long long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&(data->print));
	if (!is_philo_dead(data) || dead == 1)
	{
		printf("%lld %d ", current_time - data->start_time, philo + 1);
		printf("%s\n", status);
	}
	pthread_mutex_unlock(&(data->print));
}

// Usleep time (eat, sleep)
void	ft_usleep(t_data *data, long long time)
{
	long long	start;

	start = get_time();
	while (!is_philo_dead(data) && (get_time() - start) < time)
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
