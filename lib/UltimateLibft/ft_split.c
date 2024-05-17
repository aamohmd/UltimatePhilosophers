/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:07:35 by aamohame          #+#    #+#             */
/*   Updated: 2023/12/16 15:50:00 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**ft_freestr(char **str, int x)
{
	while (x > 0)
	{
		x--;
		free(str[x]);
	}
	free(str);
	return (NULL);
}

static char	**ft_makestr(char **str, const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		x;

	i = 0;
	x = 0;
	while (s[i] != '\0' && s != NULL)
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > j)
		{
			str[x] = ft_substr(s, j, i - j);
			if (str[x++] == NULL)
				return (ft_freestr(str, x));
		}
	}
	str[x] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (str == NULL)
		return (NULL);
	return (ft_makestr(str, s, c));
}
