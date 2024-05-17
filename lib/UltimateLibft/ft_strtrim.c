/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:38:17 by aamohame          #+#    #+#             */
/*   Updated: 2023/12/16 15:54:36 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checker(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_i(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && ft_checker(set, s1[i]) == 1)
		i++;
	return (i);
}

static size_t	ft_j(const char *s1, const char *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (i > ft_i(s1, set) && ft_checker(set, s1[i]) == 1)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	len;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	i = ft_i(s1, set);
	j = ft_j(s1, set);
	len = j - i + 1;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	x = 0;
	while (x < len)
	{
		str[x] = s1[i + x];
		x++;
	}
	str[x] = '\0';
	return (str);
}
