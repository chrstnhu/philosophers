/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:04:04 by chrhu             #+#    #+#             */
/*   Updated: 2024/06/10 19:34:04 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>
# include <fcntl.h> 
# include <sys/stat.h> 

# define DEFAULT "\033[0;39m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

# define SEM_FORKS "/forks"
# define SEM_DEAD "/dead"
# define SEM_PRINT "/print"
# define SEM_LAST_MEAL "/last_meal"
# define SEM_MEAL "/meal"
# define SEM_ALL_ATE "/all_ate"

# define NB_MAX      220

struct	s_data;

typedef struct s_philo
{
	int				philo;
	int				philo_ate;
	long long		last_meal;
	struct s_data	*data;
	pthread_t		threads;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_eat;
	bool			philo_dead;
	bool			all_ate;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meal_check;
	sem_t			*dead_check;
	sem_t			*lastmeal_check;
	sem_t			*all_ate_check;
	t_philo			philo[NB_MAX];
}	t_data;

// Number
int			check_number(int argc, char **argv);
int			ft_atoi(const char *nptr);

// Initialize
int			init_thread(t_data *data);
int			init_mutex(t_data *data);
int			init_philo(t_data *data);
int			initialize(t_data *data, char **argv);
void		thread_wait_destroy(t_data *data, t_philo *philo);

// Execution
void		*action(void *philosopher);
void		philo_eating(t_philo *philo, t_data *data);

// Calcul time
void		ft_usleep(t_data *data, long long time);
long long	get_time(void);
void		print_status(t_data *data, int philo, const char *status, int dead);

// Check
void		check_dead(t_data *data, t_philo *philo);
int			philo_status(t_data *data);
int			philo_all_ate(t_data *data);
int			number_of_meals(t_data *data, int philo_id);

#endif
