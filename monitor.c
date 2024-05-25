/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:13:38 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/25 12:13:45 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*monitor(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)arg;
	philo = data->philos;
	while (1)
	{
		if (philo->is_dead == 1)
			return (NULL);
		philo = philo->next;
		if (philo == NULL)
			philo = data->philos;
	}
	return (NULL);
}