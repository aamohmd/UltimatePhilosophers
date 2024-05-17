/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:37:22 by aamohame          #+#    #+#             */
/*   Updated: 2023/12/13 11:06:11 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t len)
{
	char	*dest;
	char	*src;

	dest = (char *)destination;
	src = (char *)source;
	if (source < destination)
	{
		while (len > 0)
		{
			len--;
			dest[len] = src[len];
		}
		return (destination);
	}
	else
	{
		return (ft_memcpy(destination, source, len));
	}
}
