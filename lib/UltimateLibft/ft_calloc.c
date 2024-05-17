/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:43:29 by aamohame          #+#    #+#             */
/*   Updated: 2023/12/23 14:10:39 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*null;
	size_t	total_size;

	total_size = count * size;
	if (total_size != 0 && count != total_size / size)
		return (NULL);
	null = malloc(count * size);
	if (null == NULL)
		return (NULL);
	ft_bzero(null, count * size);
	return (null);
}
