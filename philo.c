/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:43:42 by aamohame          #+#    #+#             */
/*   Updated: 2024/08/30 12:57:48 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	setup_forks(t_data *data)
{
	t_philo	*head;

	data->stop_condition = 0;
	data->nb_eat = 0;
	head = data->philos;
	while (head->next)
	{
		head->left_fork = &(head->next->right_fork);
		head = head->next;
	}
	head->left_fork = &(data->philos->right_fork);
}

void	setup_data(t_philo *new_philo, t_data *data)
{
	new_philo->time_to_die = data->time_to_die;
	new_philo->time_to_eat = data->time_to_eat;
	new_philo->time_to_sleep = data->time_to_sleep;
	new_philo->nb_must_eat = data->nb_must_eat;
	new_philo->nb_eat = 0;
	new_philo->is_dead = 0;
	new_philo->thread = 0;
	pthread_mutex_init(&(new_philo->right_fork), NULL);
	new_philo->dead = &(data->dead);
	new_philo->meal = &(data->meal);
	new_philo->print = &(data->print);
}

void	setup_philos(t_data *data)
{
	t_philo	*new_philo;
	t_philo	*tmp;
	int		i;

	i = 0;
	data->philos = NULL;
	while (i < data->nb_philo)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		new_philo->philo_id = i + 1;
		setup_data(new_philo, data);
		new_philo->data = data;
		new_philo->next = NULL;
		if (data->philos == NULL)
			data->philos = new_philo;
		else
		{
			tmp = data->philos;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new_philo;
		}
		i++;
	}
}

int	setup_env(t_data *data, char **argv)
{
	if (data_correct(argv) == 0)
		return (printf("Error: Arguments must be positive integers\n"), 1);
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo < 1 || data->nb_philo > 200)
		return (printf("Number of philosophers must be between 1 and 200\n"),
			1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep < 60 || data->time_to_eat < 60
		|| data->time_to_die < 60)
		return (printf("Error: Time must be at least 60ms\n"), 1);
	if (argv[5])
	{
		data->nb_must_eat = ft_atoi(argv[5]);
		if (data->nb_must_eat == -1 || data->nb_must_eat == 0)
			return (printf("Error: Number of times\n"),
				1);
	}
	else
		data->nb_must_eat = 0;
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&(data->dead), NULL);
	pthread_mutex_init(&(data->meal), NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*head;

	if (argc < 5)
		return (printf("Error: Wrong number of arguments\n"), 1);
	if (setup_env(&data, argv))
		return (1);
	setup_philos(&data);
	setup_forks(&data);
	head = data.philos;
	data.start = get_current_time();
	while (head)
	{
		head->last_meal = data.start;
		pthread_create(&head->thread, NULL, philo_routine, head);
		head = head->next;
	}
	philo_dead(&data);
	head = data.philos;
	while (head)
	{
		pthread_join(head->thread, NULL);
		head = head->next;
	}
	return (free_all(&data), 0);
}
