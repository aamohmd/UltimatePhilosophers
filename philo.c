/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:43:42 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/25 19:39:38 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	setup_forks(t_data *data)
{
	t_philo	*head;

	head = data->philos;
	while (head->next)
	{
		head->left_fork = &(head->next->right_fork);
		head = head->next;
	}
	head->left_fork = &(data->philos->right_fork);
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

void	setup_env(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_must_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&(data->dead), NULL);
	pthread_mutex_init(&(data->meal), NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*head;
	pthread_t	monitor;

	if (argc < 5)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	setup_env(&data, argv);
	setup_philos(&data);
	setup_forks(&data);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	head = data.philos;
	while (head)
	{
		pthread_create(&head->thread, NULL, philo_routine, head);
		head = head->next;
	}
	pthread_join(monitor, NULL);
	head = data.philos;
	while (head)
	{
		pthread_join(head->thread, NULL);
		head = head->next;
	}
	return (0);
}
