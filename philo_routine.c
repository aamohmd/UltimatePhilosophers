/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:32 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/25 12:16:05 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(philo->dead), 1);
	pthread_mutex_unlock(philo->dead);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->print);
	printf("%zu %d %s\n", get_current_time() - philo->start, philo->philo_id, status);
	pthread_mutex_unlock(philo->print);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start = get_current_time();
	if (philo->philo_id >= 0)
	{
		print_status(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
	}
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->right_fork));
		print_status(philo, "is eating");
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&(philo->right_fork));
		print_status(philo, "is thinking");
	}
	return (NULL);
}