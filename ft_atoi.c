/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:31:49 by aamohame          #+#    #+#             */
/*   Updated: 2024/08/30 12:44:49 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483647 && sign == -1)
			return (0);
		str++;
	}
	return (result * sign);
}
