/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:53:58 by nabentay          #+#    #+#             */
/*   Updated: 2022/07/30 22:43:24 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (--dstsize && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

static int	ft_countword(char const *tab, char c)
{
	int	word;

	word = 0;
	while (*(++tab))
		if (*tab == c && *(tab + 1) != c)
			word++;
	return (word);
}

static int	ft_cnt(char const *s, char c)
{
	int	word;

	word = 0;
	while (*s && *s != c && s++)
		word++;
	return (word);
}

static void	ft_fill(char *tab, char const **s, char c)
{
	while (**s && **s != c)
	{
		*tab = **s;
		(*s)++;
		tab++;
	}
	*tab = '\0';
}

char	**ft_split(char const *s, char c)
{
	int		i2;
	char	**tab;

	i2 = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countword(s, c)) + 1);
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			tab[i2] = (char *)malloc(sizeof(char) * (ft_cnt(s, c) + 1));
			ft_fill(tab[i2], &s, c);
			i2++;
		}
		else
			s++;
	}
	tab[i2] = 0;
	return (tab);
}
