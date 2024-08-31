/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:33:43 by aamohame          #+#    #+#             */
/*   Updated: 2024/08/30 10:11:00 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_all(t_data *data)
{
	t_philo	*head;
	t_philo	*tmp;

	head = data->philos;
	while (head)
	{
		tmp = head->next;
		pthread_mutex_destroy(&head->right_fork);
		free(head);
		head = tmp;
	}
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->print);
}

int	data_correct(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_dead(t_philo *head, t_data *data)
{
	while (head)
	{
		pthread_mutex_lock(&data->meal);
		if ((int)(get_current_time() - head->last_meal) >= data->time_to_die)
		{
			if (!data->stop_condition && !data->nb_eat)
			{
				print_status(head, "died", UNLOCK);
				data->stop_condition = 1;
				pthread_mutex_unlock(&data->dead);
			}
		}
		pthread_mutex_unlock(&data->meal);
		pthread_mutex_lock(&data->dead);
		if (data->stop_condition)
		{
			pthread_mutex_unlock(&data->dead);
			break ;
		}
		pthread_mutex_unlock(&data->dead);
		head = head->next;
	}
}

void	philo_dead(t_data *data)
{
	t_philo	*head;
	int		i;

	head = data->philos;
	while (!data->nb_eat)
	{
		i = -1;
		head = data->philos;
		check_dead(head, data);
		pthread_mutex_lock(&data->dead);
		if (data->stop_condition)
			return (pthread_mutex_unlock(&data->dead), (void)0);
		pthread_mutex_unlock(&data->dead);
		i = 0;
		head = data->philos;
		while (data->nb_must_eat && head && head->nb_eat >= data->nb_must_eat)
		{
			head = head->next;
			i++;
		}
		pthread_mutex_lock(&data->dead);
		data->nb_eat = (i == data->nb_philo);
		pthread_mutex_unlock(&data->dead);
		usleep(999);
	}
}
