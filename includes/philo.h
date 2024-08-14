/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:24:05 by aamohame          #+#    #+#             */
/*   Updated: 2024/08/13 11:37:28 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../lib/UltimateLibft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define LOCK 0
# define UNLOCK 1

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				nb_eat;
	int				is_dead;
	size_t			last_meal;
	size_t			start;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*meal;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				stop_condition;
	int				nb_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
	t_philo			*philos;
}					t_data;

size_t	get_current_time(void);
void	*philo_routine(void *arg);
void	print_status(t_philo *philo, char *status);
void	philo_dead(t_data *data);
int		data_correct(char **argv);

#endif
