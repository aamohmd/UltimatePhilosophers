/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:32 by aamohame          #+#    #+#             */
/*   Updated: 2024/08/29 19:08:47 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&data->dead);
		if (data->stop_condition || data->nb_eat)
		{
			pthread_mutex_unlock(&data->dead);
			return (0);
		}
		pthread_mutex_unlock(&data->dead);
		usleep(80);
	}
	return (0);
}

void	print_status(t_philo *philo, char *status, int lock)
{
	pthread_mutex_lock(philo->dead);
	if (!philo->data->stop_condition && !philo->data->nb_eat)
	{
		printf("%zu %d %s\n", get_current_time() - philo->data->start,
			philo->philo_id, status);
	}
	if (lock == LOCK)
		pthread_mutex_unlock(philo->dead);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", LOCK);
	if (philo->left_fork == &philo->right_fork)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&(philo->right_fork));
	print_status(philo, "has taken a fork", LOCK);
	print_status(philo, "is eating", LOCK);
	pthread_mutex_lock(philo->meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal);
	ft_usleep(philo->time_to_eat, philo->data);
	pthread_mutex_lock(philo->dead);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->dead);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
	{
		print_status(philo, "is sleeping", LOCK);
		ft_usleep(philo->time_to_sleep, philo->data);
	}
	while (1)
	{
		pthread_mutex_lock(philo->dead);
		if (philo->data->stop_condition || philo->data->nb_eat)
		{
			pthread_mutex_unlock(philo->dead);
			break ;
		}
		pthread_mutex_unlock(philo->dead);
		print_status(philo, "is thinking", LOCK);
		if (eat(philo) == 1)
			break ;
		print_status(philo, "is sleeping", LOCK);
		ft_usleep(philo->time_to_sleep, philo->data);
	}
	return (NULL);
}
